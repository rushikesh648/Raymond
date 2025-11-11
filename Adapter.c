void handle_adapter_power(int voltage) {
    if (get_current_source() != SOURCE_ADAPTER) {
        // Switch to the stable adapter power source
        set_power_source(SOURCE_ADAPTER);
        
        // Start the battery charging process
        start_charging(); 
        log_event("Adapter connected. Switched to external power and charging started.");
    }
    
    if (voltage >= BATTERY_LOW_THRESHOLD_MV) {
        // If battery is low, indicate fast charging (optional)
        set_led_indicator(LED_FAST_CHARGE);
    }
    // Note: The charging circuit hardware handles the actual charge control.
}
