# Plant Watering System

I want to make a semi-automatic plant watering/agriculture system. I could see this being used on plants around the house. It could even be expanded to a larger system within a greenhouse.

## 1. The single plant approach

This approach would be able to service a single plant.

A single SoC should have an LCD that displays metrics about the plant (soil moisture, tank water level, ambient temperature, light level). The plant pot should have a soil moisture sensor to help determine when to water the plant. A photoresistor to determine how long the plant has received light. A RGB LED to help show how much water is left in the tank.

*Components needed for this project:*
- LCD
- Button
- Soil moisture sensor
- Water level sensor
- Photoresistor
- Relay (to simulate water pump)
- RGB LED

## 2. The multiple plant approach

This approach would be able to service multiple plants around the house.

A single SoC should act as the master node, and it should be located somewhere central in the house. It should have an LCD that displays information about the plants and air humidity conditions around the house. It should have a button to cycle through information. It should have a RF Tranceiver to communicate with slave nodes.

Every plant in the house needs a smaller SoC board, and it should act as a slave node. It should have the same sensors as the single plant approach except the LCD and the button.

The slaves should broadcast metrics about their respective plants every 30 - 60 seconds and the master node should use the metrics to determine what the slave should do. It should save the metrics in a time series database. It should send the slaves tasks to perform, like turning on the pump for a specific amount of time.
