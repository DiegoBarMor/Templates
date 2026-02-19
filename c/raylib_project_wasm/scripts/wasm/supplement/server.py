#!/usr/bin/env python3

##### ADAPTED FROM SUGGESTED SCRIPT BY COPILOT.
##### TESTED AND CLEANED UP ACCORDINGLY.

import sys
import tty
import http.server
import socketserver
import select
import threading
import termios

PORT = int(sys.argv[1])

# //////////////////////////////////////////////////////////////////////////////
class HandlerCloseWithTabClose(http.server.SimpleHTTPRequestHandler):
    def do_POST(self):
        if self.path == "/__close":
            # mark stop event (if present) so main loop can exit,
            # then request server shutdown from a separate thread
            stop_ev = getattr(self.server, "stop_event", None)
            if stop_ev is not None:
                stop_ev.set()
            self.send_response(204)
            self.end_headers()
            threading.Thread(target=self.server.shutdown, daemon=True).start()
        else:
            self.send_response(404)
            self.end_headers()


# //////////////////////////////////////////////////////////////////////////////
class StoppableServer(socketserver.ThreadingTCPServer):
    allow_reuse_address = True


# ------------------------------------------------------------------------------
def main():
    srv = StoppableServer(("0.0.0.0", PORT), HandlerCloseWithTabClose)
    stop_event = threading.Event()
    srv.stop_event = stop_event

    def serve():
        try:
            srv.serve_forever()
        except KeyboardInterrupt:
            pass
        finally:
            srv.server_close()

    thread = threading.Thread(target=serve)
    thread.daemon = True
    thread.start()


    fd = sys.stdin.fileno()
    old_attrs = None
    try:
        old_attrs = termios.tcgetattr(fd)
        tty.setraw(fd)
        while True:
            if stop_event.is_set(): break

            r, _, _ = select.select([sys.stdin], [], [], 0.1)
            if not r: continue

            ch = sys.stdin.read(1)
            if ch != 'q': continue

            stop_event.set()
            break

    except Exception:
        pass

    finally:
        if old_attrs is not None:
            try: termios.tcsetattr(fd, termios.TCSADRAIN, old_attrs)
            except Exception: pass
        try:
            srv.shutdown()
            thread.join()
        except Exception:
            pass


################################################################################
if __name__ == "__main__":
    main()


################################################################################
