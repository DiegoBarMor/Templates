package com.diegobarmor.boilerplate.ui

import androidx.lifecycle.ViewModel
import com.diegobarmor.boilerplate.data.BoilerplateUiState
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow

class BoilerplateViewModel : ViewModel() {
    private val _uiState = MutableStateFlow(BoilerplateUiState())
    val uiState: StateFlow<BoilerplateUiState> = _uiState.asStateFlow()
}
