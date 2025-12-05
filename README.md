# H4_IoT_external_door_lock

This project uses 2 arduino's to communicate to Home Assistant, for unlocking and locking doors.
One arduino handles authentication for locking and unlocking the door, using a keypad and RFID.
The other arduino handles physically locking and unlocking the door.

The Arduino's are using MQTT to communicate to Home Assistant.

The lock can also be enabled and disabled, from Home Assistant itself, without using RFID or the keypad.
