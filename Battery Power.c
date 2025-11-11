void handle_battery_power(int voltage) {
    // If running on adapter and adapter is suddenly removed
    if (get_current_source() != SOURCE_BATTERY) {
        set_power_source(SOURCE_BATTERY);
        stop_charging();
        log_event("Adapter disconnected. Switched to battery power.");
    }

    // Monitor critical voltage levels
    if (voltage <= BATTERY_CRITICAL_MV) {
        // Critical shutdown sequence
        set_led_indicator(LED_CRITICAL);
        log_event("CRITICAL: Battery at 3.0V. Initiating safe shutdown.");
        // Call a system function to cleanly shut down the main application processor
        system_shutdown(); 
    } else if (voltage <= BATTERY_LOW_THRESHOLD_MV) {
        // Low power warning
        set_led_indicator(LED_LOW_BATTERY);
        log_event("WARNING: Battery low. Please connect power adapter.");
    } else {
        // Normal operation
        set_led_indicator(LED_NORMAL);
    }
}
