# worst keyboard ever

## demo

[![Alt text](https://cloud-a42ea3urd-hack-club-bot.vercel.app/0demo.jpg)](https://www.youtube.com/shorts/FnlSxVaX2-Q)

## wiring

### display (nokia 5110)

- RST -> GPIO4
- CE -> GPIO5
- DC -> GPIO16
- DIN -> GPIO23
- CLK -> GPIO18
- VCC -> 5V
- BL -> 3V3
- GND -> GND

### other electronics

- space button to GPIO25
- potentiometer to GPIO26
- submit button to GPIO27

## usage

- after all the wiring is done, connect the esp32 to the pc with a serial usb cable and upload the code using platformio.
- there's a scripts folder in the repo which has a python script `main.py` that reads the serial output of the esp32. run that script and enjoy the worst keyboard ever made.
- note: install the `pyserial` and `pyautogui` module before running the python script using `pip`.

---

thanks!
