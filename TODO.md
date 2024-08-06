# Further Scope of Project

I'm trying to further expand this project and release the next version of the software with more better interface.

## Goals

- Migrating to latest nRF SDK release which is v2.7.0 as of today. This is the highest priroty item to pick up. Since nRF has updated alot after the project.
- Providing a way to user to Register/Unregister new commands via API's and their associated work handler.
- Interface layer to user for the available transport protocol. They can just glue it their way.
- Supporting network transport protocols like MQTT, CoAP, HTTP
- Adding timeout in the CLI scripts.

## New Interface would go like this,

```
// start new session
void nRFDude_SessionCreate();

// Release the session
void nRFDude_SessionDestroy();

// Processing the cmd
void nRFDude_SessionProcess();

// Respond to cmd
void nRFDude_SessionRespond();

// Register the cmd
void nRFDude_RegisterCmd(...);

// Unregister the cmd
void nRFDude_UnregisterCmd(...);
```