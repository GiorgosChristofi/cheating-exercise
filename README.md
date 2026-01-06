## This project was created to pass the cheating exercise in Secret Affairs 2. 
The exercise rewarded successful students with 1 bonus point in the final exam. The participants had 15 minutes to write down in a marked piece of paper the first 200 digits of the golden ratio, even though many students simply memorized them I decided that it was against the spirit of the exercise and thus devised the following contraption.

![IMG_3682](https://github.com/user-attachments/assets/28a7c20a-2fcc-4435-8acc-088b89ff45c6)

It consisted of 2 vibration modules (choosen specifically due to their silent operation if ran low enough), 1 (3x AAA) battery pack, 2 buttons (1 regular button that comes in arduino kits but since it was too audible I also ripped out a button from an old pair of disfunctional ear pieces), 1 arduino nano (choosen for its small form factor).

The vibration motors were taped to my legs, each vibrating from 1 to 5 times. The left leg translated to the digits 1-5 and the right leg to 6-0 (depending on the amount of vibrations). Alternative methods of encoding were tested but this one was ultimately choosen for its simplicity and easy of decoding.

The message was broken down into 10 blocks of 20 digits, and the buttons were used to switch between blocks (1 press = next block, 2 presses = repeat block, 3 presses = previous block)

In the end, my method of cheating was not discovered by the invidulators and I was able to successfully pass this exercise.
