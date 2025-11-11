void main() {
    // 1. Initialization
    setup_gpio();
    initialize_adc();
    set_power_source(SOURCE_BATTERY); // Start on battery by default

    // 2. Main System Loop
    while (1) {
        // Read the current state of the system
        bool adapter_present = digital_read(PIN_STATUS_ADAPTER_DETECT);
        int battery_voltage = read_battery_voltage(PIN_ADC_BATTERY_VOLTAGE);

        if (adapter_present) {
            // Case A: Adapter is plugged in
            handle_adapter_power(battery_voltage);
        } else {
            // Case B: Running on battery
            handle_battery_power(battery_voltage);
        }

        // Delay to prevent excessive checking/power consumption
        delay_ms(500);
    }
}
