/**
 * \file htu21d.h
 *
 * \brief htu21 Temperature & Humidity sensor driver header file
 *
 * Copyright (c) 2016 Measurement Specialties. All rights reserved.
 *
 */

#ifndef HTU21_H_INCLUDED
#define HTU21_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

// Enums
enum htu21_i2c_master_mode {
	htu21_i2c_hold,
	htu21_i2c_no_hold
};

enum htu21_status {
	htu21_status_ok,
	htu21_status_no_i2c_acknowledge,
	htu21_status_i2c_transfer_error,
	htu21_status_crc_error
};

enum htu21_resolution {
	htu21_resolution_t_14b_rh_12b = 0,
	htu21_resolution_t_12b_rh_8b,
	htu21_resolution_t_13b_rh_10b,
	htu21_resolution_t_11b_rh_11b
};

enum htu21_battery_status {
	htu21_battery_ok,
	htu21_battery_low
};

enum htu21_heater_status {
	htu21_heater_off,
	htu21_heater_on
};

// Functions

/**
 * \brief Configures the SERCOM I2C master to be used with the HTU21 device.
 */
void htu21_init(void);

/**
 * \brief Check whether HTU21 device is connected
 *
 * \return bool : status of HTU21
 *       - true : Device is present
 *       - false : Device is not acknowledging I2C address
 */
bool htu21_is_connected(void);

/**
 * \brief Reset the HTU21 device
 *
 * \return htu21_status : status of HTU21
 *       - htu21_status_ok : I2C transfer completed successfully
 *       - htu21_status_i2c_transfer_error : Problem with i2c transfer
 *       - htu21_status_no_i2c_acknowledge : I2C did not acknowledge
 */
enum htu21_status htu21_reset(void);

/**
 * \brief Reads the htu21 serial number.
 *
 * \param[out] uint64_t* : Serial number
 *
 * \return htu21_status : status of HTU21
 *       - htu21_status_ok : I2C transfer completed successfully
 *       - htu21_status_i2c_transfer_error : Problem with i2c transfer
 *       - htu21_status_no_i2c_acknowledge : I2C did not acknowledge
 *       - htu21_status_crc_error : CRC check error
 */
enum htu21_status htu21_read_serial_number(uint64_t *);

/**
 * \brief Set temperature and humidity ADC resolution.
 *
 * \param[in] htu21_resolution : Resolution requested
 *
 * \return htu21_status : status of HTU21
 *       - htu21_status_ok : I2C transfer completed successfully
 *       - htu21_status_i2c_transfer_error : Problem with i2c transfer
 *       - htu21_status_no_i2c_acknowledge : I2C did not acknowledge
 *       - htu21_status_crc_error : CRC check error
 */
enum htu21_status htu21_set_resolution(enum htu21_resolution);

/**
 * \brief Set I2C master mode. 
 *        This determines whether the program will hold while ADC is accessed or will wait some time
 *
 * \param[in] htu21_i2c_master_mode : I2C mode
 *
 */
void htu21_set_i2c_master_mode(enum htu21_i2c_master_mode);

/**
 * \brief Reads the relative humidity value.
 *
 * \param[out] float* : Celsius Degree temperature value
 * \param[out] float* : %RH Relative Humidity value
 *
 * \return htu21_status : status of HTU21
 *       - htu21_status_ok : I2C transfer completed successfully
 *       - htu21_status_i2c_transfer_error : Problem with i2c transfer
 *       - htu21_status_no_i2c_acknowledge : I2C did not acknowledge
 *       - htu21_status_crc_error : CRC check error
 */
enum htu21_status htu21_read_temperature_and_relative_humidity( float *, float*);

/**
 * \brief Provide battery status
 *
 * \param[out] htu21_battery_status* : Battery status
 *                      - htu21_battery_ok,
 *                      - htu21_battery_low
 *
 * \return status of HTU21
 *       - htu21_status_ok : I2C transfer completed successfully
 *       - htu21_status_i2c_transfer_error : Problem with i2c transfer
 *       - htu21_status_no_i2c_acknowledge : I2C did not acknowledge
 */
enum htu21_status htu21_get_battery_status(enum htu21_battery_status*);

/**
 * \brief Enable heater
 *
 * \return htu21_status : status of HTU21
 *       - htu21_status_ok : I2C transfer completed successfully
 *       - htu21_status_i2c_transfer_error : Problem with i2c transfer
 *       - htu21_status_no_i2c_acknowledge : I2C did not acknowledge
 */
enum htu21_status htu21_enable_heater(void);

/**
 * \brief Disable heater
 *
 * \return htu21_status : status of HTU21
 *       - htu21_status_ok : I2C transfer completed successfully
 *       - htu21_status_i2c_transfer_error : Problem with i2c transfer
 *       - htu21_status_no_i2c_acknowledge : I2C did not acknowledge
 */
enum htu21_status htu21_disable_heater(void);

/**
 * \brief Get heater status
 *
 * \param[in] htu21_heater_status* : Return heater status (above or below 2.5V)
 *	                    - htu21_heater_off,
 *                      - htu21_heater_on
 *
 * \return htu21_status : status of HTU21
 *       - htu21_status_ok : I2C transfer completed successfully
 *       - htu21_status_i2c_transfer_error : Problem with i2c transfer
 *       - htu21_status_no_i2c_acknowledge : I2C did not acknowledge
 */
enum htu21_status htu21_get_heater_status(enum htu21_heater_status*);

/**
 * \brief Returns result of compensated humidity
 *
 * \param[in] float - Actual temperature measured (degC)
 * \param[in] float - Actual relative humidity measured (%RH)
 *
 * \return float - Compensated humidity (%RH).
 */
float htu21_compute_compensated_humidity(float,float);

/**
 * \brief Returns the computed dew point
 *
 * \param[in] float - Actual temperature measured (degC)
 * \param[in] float - Actual relative humidity measured (%RH)
 *
 * \return float - Dew point temperature (DegC).
 */
float htu21_compute_dew_point(float,float);

#endif /* HTU21_H_INCLUDED */