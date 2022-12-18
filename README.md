# Arduino Enhanced Railroad Crossing #
***DRAFT***
There are many example sketches on the internet for railroad crossings. However most of the ones I found did not support more than one track. I am also new to Arduino so be kind, I may miss something. If you like this concept feel free to use this code. I however am doing this for free/fun so no warranty is implied. Use at your own risk.

I have some more testing to do and will update the code as I find things.

Open an issue if you have a comment, idea or bug.

# My Coding Environment #
- Windows 10
- Visual Studio Code, I started with Arduino IDE but found this much better, for me.
    Extensions - TODO
- PlatformIO

# My Hardware #
Not sponsored by Amazon but a easy fairly inexpensive place to get stuff with good shipping. I am a member of Amazon prime.
These are just what I used. You can substitute as you see fit, just change the code.
- Arduino Uno - program takes about 13k, mega will work.
    https://www.amazon.com/dp/B01EWOE0UU?psc=1&ref=ppx_yo2ov_dt_b_product_details
- Infrared sensors, I used 4
    https://www.amazon.com/dp/B07FJLMLVZ?psc=1&ref=ppx_yo2ov_dt_b_product_details
- LCD 1, 16 x 2
    https://www.amazon.com/dp/B07D83DY17?psc=1&ref=ppx_yo2ov_dt_b_product_details
- Flasher 1, so we dont waste cpu on blinking LEDs
    https://www.amazon.com/dp/B08F3M573C?psc=1&ref=ppx_yo2ov_dt_b_product_details
- MP3 Player
    https://www.amazon.com/dp/B07Y2YKYRS?psc=1&ref=ppx_yo2ov_dt_b_product_details
- SD Card
    https://www.amazon.com/dp/B091CB7964?ref=ppx_yo2ov_dt_b_product_details&th=1
- Speaker
    https://www.amazon.com/dp/B01CHYIU26?psc=1&ref=ppx_yo2ov_dt_b_product_details
- Servo - qty 2
    https://www.amazon.com/dp/B07Q6JGWNV?psc=1&ref=ppx_yo2ov_dt_b_product_details
- LEDs - red - qty 4
    https://www.amazon.com/dp/B09XDMJ6KY?psc=1&ref=ppx_yo2ov_dt_b_product_details
- Project board
    https://www.amazon.com/Breadboards-Solderless-Breadboard-Distribution-Connecting/dp/B07DL13RZH/ref=pd_bxgy_img_sccl_1/140-3574912-4189668?pd_rd_w=8ykLm&content-id=amzn1.sym.7f0cf323-50c6-49e3-b3f9-63546bb79c92&pf_rd_p=7f0cf323-50c6-49e3-b3f9-63546bb79c92&pf_rd_r=Z9Z4XPK35P6DH893QNYZ&pd_rd_wg=lsJzb&pd_rd_r=aa49902d-7841-4429-9bf1-48bf1d527a5e&pd_rd_i=B07DL13RZH&psc=1
- Wires, any would do but I would use solid, easier.
    https://www.amazon.com/dp/B07GD2BWPY?ref=ppx_yo2ov_dt_b_product_details&th=1
- Resistors, used for the MP3 Player
    https://www.amazon.com/dp/B0185FHALI?psc=1&ref=ppx_yo2ov_dt_b_product_details
- Project holder
    https://www.amazon.com/dp/B07WCBXFD3?psc=1&ref=ppx_yo2ov_dt_b_product_details

# Libraries #
- Arduino-LiquidCrystal-I2C, there are many out there. I tried about 4, most would cause the Arduino to hang.
- DFRobotDFPlayerMini
- SoftwareSerial
- and of course Arduino

# Some problems I tried to solve #
- No use of delay
- Event driven so we dont miss anything
- 2 tracks
- Either track either direction
- Trains can enter and leave at different times and speeds
- Short or long trains
- Either train can stop and back out

# Diagram #
TODO
