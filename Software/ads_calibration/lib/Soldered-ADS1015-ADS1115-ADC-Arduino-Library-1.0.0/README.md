# ADS1x15 easyC board Arduino library

[![Make docs and publish to GitHub Pages](https://github.com/SolderedElectronics/Soldered-ADS1015-ADS1115-ADC-Arduino-Library/actions/workflows/make_docs.yml/badge.svg?branch=dev)](https://github.com/SolderedElectronics/Soldered-ADS1015-ADS1115-ADC-Arduino-Library/actions/workflows/make_docs.yml)
[![Arduino Library Manager Compatibility](https://github.com/SolderedElectronics/Soldered-ADS1015-ADS1115-ADC-Arduino-Library/actions/workflows/arduino_lint.yml/badge.svg?branch=dev)](https://github.com/SolderedElectronics/Soldered-ADS1015-ADS1115-ADC-Arduino-Library/actions/workflows/arduino_lint.yml)


| ![ADC 12-bit ADS1015 4-channel with PGA breakout](https://github.com/SolderedElectronics/ADC-12-bit-ADS1015-4-channel-with-PGA-breakout-hardware-design/blob/main/OUTPUTS/V1.1.1/333094.jpg) |
| :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| [ADC 12-bit ADS1015 4-channel with PGA breakout](https://www.solde.red/333094) |

| ![ADC 16-bit ADS1115 4-channel with PGA breakout](https://github.com/SolderedElectronics/ADC-16-bit-ADS1115-4-channel-with-PGA-breakout-hardware-design/blob/main/OUTPUTS/V1.1.1/333095.jpg) |
| :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
|                                                        [ADC 16-bit ADS1115 4-channel with PGA breakout](https://www.solde.red/333095)                                                        |

ADC (Analog Digital Converter) is a device that reads analog signals (just like the analogRead () function in Arduino IDE) and converts them into a digital signal that can be read by a microcontroller. This breakout is based on the ADS1115 ADC, which reads values in 12-bit resolution, receives a maximum of 3.3V on its inputs and has a total of 4 channels (which can also be used as two differential). Works great with each microcontroller at 5V. It has 2 easyC connectors for easier connection on I2C communication.

You can find more about easyC at this link.

- Voltage: 3.3V
- Resolution: 12-bit
- Number of channels: 4
- I2C communication
- Dimensions: 22 x 22 mm (https://www.soldered.com/en/easyC)

ADC (Analog Digital Converter) is a device that reads analog signals (just like the analogRead () function in Arduino IDE) and converts them into a digital signal that can be read by a microcontroller. This breakout is based on the ADS1115 ADC, which reads values in 16-bit resolution, receives a maximum of 3.3V on its inputs and has a total of 4 channels (which can also be used as two differential). Works great with each microcontroller at 5V. It has 2 easyC connectors for easier connection on I2C communication.

You can find more about easyC at this link.

- Voltage: 3.3V
- Resolution: 16-bit
- Number of channels: 4
- I2C communication
- Dimensions: 22 x 22 mm

### Repository Contents

- **/src** - source files for the library (.h & .cpp)
- **/examples** - examples for using the library
- **_other_** - _keywords_ file highlights function words in your IDE, _library.properties_ enables implementation with Arduino Library Manager.

### Hardware design

You can find hardware design for this board in [_ADC 12-bit ADS1015 4-channel with PGA breakout_](https://github.com/SolderedElectronics/ADC-12-bit-ADS1015-4-channel-with-PGA-breakout-hardware-design) hardware repository.

You can find hardware design for this board in [_ADC 16-bit ADS1115 4-channel with PGA breakout_](https://github.com/SolderedElectronics/ADC-16-bit-ADS1115-4-channel-with-PGA-breakout-hardware-design) hardware repository.

### Documentation

Access Arduino library documentation [here](https://SolderedElectronics.github.io/Soldered-ADS1015-ADS1115-ADC-Arduino-Library/).

- Tutorial for using the ADS1x15 easyC board
- Installing an Arduino library

### Board compatibility

The library is compatible with board & microcontroller families shown in green below:

[![Compile Sketches](http://github-actions.40ants.com/e-radionicacom/Soldered-ADS1015-ADS1115-ADC-Arduino-Library/matrix.svg?branch=dev&only=Compile%20Sketches)](https://github.com/SolderedElectronics/Soldered-ADS1015-ADS1115-ADC-Arduino-Library/actions/workflows/compile_test.yml)

### About Soldered

<img src="https://raw.githubusercontent.com/e-radionicacom/Soldered-Generic-Arduino-Library/dev/extras/Soldered-logo-color.png" alt="soldered-logo" width="500"/>

At Soldered, we design and manufacture a wide selection of electronic products to help you turn your ideas into acts and bring you one step closer to your final project. Our products are intented for makers and crafted in-house by our experienced team in Osijek, Croatia. We believe that sharing is a crucial element for improvement and innovation, and we work hard to stay connected with all our makers regardless of their skill or experience level. Therefore, all our products are open-source. Finally, we always have your back. If you face any problem concerning either your shopping experience or your electronics project, our team will help you deal with it, offering efficient customer service and cost-free technical support anytime. Some of those might be useful for you:

- [Web Store](https://www.soldered.com/shop)
- [Tutorials & Projects](https://soldered.com/learn)
- [Community & Technical support](https://soldered.com/community)

### Original source

​
This library is possible thanks to original [ADS1X15](https://github.com/RobTillaart/ADS1X15) library. Thank you, RobTillaart.

### Open-source license

Soldered invests vast amounts of time into hardware & software for these products, which are all open-source. Please support future development by buying one of our products.

Check license details in the LICENSE file. Long story short, use these open-source files for any purpose you want to, as long as you apply the same open-source licence to it and disclose the original source. No warranty - all designs in this repository are distributed in the hope that they will be useful, but without any warranty. They are provided "AS IS", therefore without warranty of any kind, either expressed or implied. The entire quality and performance of what you do with the contents of this repository are your responsibility. In no event, Soldered (TAVU) will be liable for your damages, losses, including any general, special, incidental or consequential damage arising out of the use or inability to use the contents of this repository.

## Have fun!

And thank you from your fellow makers at Soldered Electronics.
