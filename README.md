# Uni-Polar Programmed Supercapacitor

Arduino and ESP8266 sketches for monitoring a storage cell's voltage and switching a relay, built for the Uni-Polar Programmed Supercapacitor (UPPSC) project. The original project pitch is kept at the bottom of this file.

## What is in this repo

| Sketch | Board | What it does |
| --- | --- | --- |
| `Arduino Code -S.ino` | Arduino (AVR) | The cleaned-up controller. Reads a voltage on `A0` (0 to 1023 mapped to 0 to 2500 mV, plus a 20 mV calibration offset), smooths it with an exponential moving average, and drives a relay on pin 8 with hysteresis (switches on at 12.2 V or more, off at 11.8 V or less, as configured). Prints voltage and relay state once per second at 9600 baud. A servo is attached on pin 9 but not used |
| `Arduino Code -test/`, `Arduino generic load/`, `arduino-zero/` | Arduino | Earlier test and load variants of the same idea: relay on pin 8, 20 mV offset, an energy counter |
| `BMS_modified.ino` | ESP8266 | Battery monitor with a 16x2 I2C LCD (address `0x27`), a relay on `D5`, and a small web page served over the board's own Wi-Fi access point |
| `BatteryMonitoringWEBPagesketch_apr19e.ino` | ESP8266 | An earlier version of the web-page monitor |

The ESP8266 sketches need the `ESPAsyncTCP`, `ESPAsyncWebServer` and `LiquidCrystal_I2C` libraries.

## Before you use these on real hardware

- **Change the Wi-Fi password.** Both ESP8266 sketches create an access point with the password `12345678` hard-coded in the source. Set your own before deploying.
- **Check the thresholds.** The relay limits (12.2 V and 11.8 V) and the `A0` scaling assume one particular voltage divider. Recalibrate for your circuit.
- These are prototype sketches and have not been through any safety review. Do not rely on them to protect a battery or a load.

# Project pitch (original write-up)

The text below is the original project description. The performance and market statements in it are claims from the pitch, not results measured by the code in this repo.

## Uni-Polar-Programmed-Supercapacitor

### (1) Sustainable Renewable Energy Storage Problems
The Electro-Spark Engine, now known as Uni-polar programmed supercapacitors (UPPSCs) is a promising innovation that has the potential to revolutionize the energy storage sector. Businesses can gain from UPPSC technology's high power and energy density, quick charging time, longer lifespan, increased safety, and reliable power transmission. Businesses that specialize in UPPSC technology have the chance to profit from this expanding market as demand for sustainable and environmentally friendly energy storage solutions rises. The fact that UPPSCs are safer to use, less expensive to make than conventional batteries, and release less pollution can be advantageous for businesses that produce and distribute UPPSCs.

UPPSC technology is especially well suited for applications with limited weight and area, making it the perfect choice for usage in electric vehicles, renewable energy storage systems, and backup power systems. As more companies use UPPSC technology, we may anticipate higher efficiency and lower prices in these sectors.

### (2) Problem Statement

#### The widespread use of traditional battery systems in various industries has resulted in several issues:

(a)Limited power and energy density                                                                                                                                                                                               
(b)Slow charging time short lifespan	                                                                                                                                      
(c)Safety hazards	
                                                                                                                   
(d)Price 1.5x expensive	

(e)Non-Recyclable

(f)Energy Density < 200 wh/kg

### (3) Solution

The intended market, production capacity, and distribution channels are only a few of the variables that will influence the UPPSCs' business model

(a)	To start, UPPSCs have the potential to be applied in several sectors, including consumer electronics, aerospace, defense, renewable energy storage, electric vehicles, and consumer electronics. As a result, the UPPSC business model may be created to appeal to particular industries or a larger market. For instance, the business can concentrate on creating and marketing UPPSCs for electric vehicles. To do this, it might collaborate with automakers or establish its production facility. In contrast, the business might decide to create UPPSCs for various industries and sell them through a variety of channels, including distributors, wholesalers, and online marketplaces.

(b) The production capacity is another crucial component of the company concept. According to market demand and the available resources, the organization would need to identify the ideal production capacity. The design, production, and testing of the UPPSCs may necessitate a sizeable investment in manufacturing facilities, research and development, and the hiring of qualified staff. To guarantee a steady supply of high-quality raw materials for the production of UPPSCs, the company might also need to establish partnerships or collaborations with suppliers.

(c)	Regarding distribution, the company may decide to build its distribution network or form relationships with current manufacturers or suppliers to include UPPSCs in their products. The business may decide to sell directly to end customers, through distributors, wholesalers, or online marketplaces, depending on the target market. It is crucial to keep in mind that the distribution strategy will also be influenced by the certifications and legal requirements for UPPSCs in various regions.

(d)	Finally, the pricing methods that would enable the business to maintain its competitiveness while still making a profit would need to be incorporated into the business model. To identify the best pricing for UPPSCs, a thorough review of production costs, market demand, and the competitive environment may be necessary. To encourage customers to migrate to UPPSCs, the business may decide to establish different prices for various markets or products, or it may decide to provide discounts and promotions.

Overall, the UPPSC industry offers businesses a special chance to offer cutting-edge, sustainable energy storage solutions to a developing market. Businesses that specialize in UPPSC technology have a great opportunity for growth and success because it has the ability to alter a variety of sectors. To ensure long-term success and profitability, the business model for UPPSCs would need to take into account several variables, including the target market, manufacturing capacity, distribution networks, and pricing strategies.

### (3) Wireframing/Architecture of the project flow

![image](https://github.com/0xShubh4m/Uni-Polar-Programmed-Supercapacitor/assets/130799986/6ab47739-2be4-4695-b7fb-e7337edadb58)

## License

[MIT](LICENSE)

---











