package com.diegobarmor.boilerplate.ui

import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.diegobarmor.boilerplate.ui.theme.BoilerplateTheme

@Composable
fun HomeScreen(
    placeholder: String,
    modifier: Modifier = Modifier
) {
    Text(
        text = placeholder,
        modifier = modifier
    )
}

@Preview
@Composable
fun HomePreview() {
    BoilerplateTheme {
        HomeScreen(
            placeholder = "Placeholder",
            modifier = Modifier.fillMaxSize()
        )
    }
}
