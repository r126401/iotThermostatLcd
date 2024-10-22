/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */


#include "esp_log.h"
#include "esp_err.h"
#include "esp_app_desc.h"
#include "logging.h"
#include "common_data.h"
#include "nvslib.h"
#include "configuracion.h"
#include "user_interface.h"
#include "conexiones.h"
#include "conexiones_mqtt.h"
#include "code_application.h"
#include "events_device.h"




#include "lv_rgb_main.h"
#include "lv_factory_reset.h"
#include "lv_thermostat.h"
#include "lv_init_thermostat.h"
#include "applib.h"

static const char *TAG = "IotThermostat";
DATOS_APLICACION datosApp;
TaskHandle_t handle;




void app_main(void) {

	/**
	 * 1.- Init data structure to Application
	 */
	init_data_app(&datosApp);
	/**
	 * 2.- init hw used in the device to specific project
	 */
	if (init_hw_device(&datosApp) != ESP_OK) {
		send_event(__func__, EVENT_ERROR_APP);
		return;

	}

	#ifdef CONFIG_USE_LCD

#ifdef CONFIG_RGB_LCD

	xTaskCreate(lv_init_lcd_application, "tarea LCD", 8192,  &datosApp, 4, NULL);
#endif
#endif

	/**
	 * 3.- Init device. the device load all configurations to work
	 */

	ESP_LOGI(TAG, ""TRAZAR"COMIENZO DE LA APLICACION version", INFOTRAZA);
	if (init_device(&datosApp) != ESP_OK) {
		ESP_LOGE(TAG,""TRAZAR" Error to initiate the device", INFOTRAZA);
		return;
	}




	/**
	 * 4.- Check if the device is in upgrade phase. If the device is not in upgrade phase,
	 * the device starting normally
	 */

	if (get_upgrade_data(&datosApp) == ESP_OK) {
		send_event(__func__, EVENT_UPGRADE_FIRMWARE);
		init_wifi_device(&datosApp);
		upgrade_ota_esp8266(&datosApp);
	} else {
		ESP_LOGI(TAG, ""TRAZAR" Device initialized succesfully", INFOTRAZA);
		init_services_device(&datosApp);
	}



	xTaskCreate(task_iotThermostat, "tarea_lectura_temperatura", CONFIG_RESOURCE_APP_TASK, (void*) &datosApp, 1, NULL);
/*
	if(is_factory() == ESP_OK) {

		send_event(__func__,EVENT_FACTORY);
	} else {

		conectar_dispositivo_wifi();
		ESP_LOGI(TAG, ""TRAZAR" ESTADO ANTES DE INICIAR GESTION: %d", INFOTRAZA, datosApp.datosGenerales->estadoApp);

	}
*/








}
