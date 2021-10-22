#include <heltec.h>

class OLED
{

public:
    // Initialize the message lines
    String messages[20] = {"", "", "", "", "", "", ""};

    // Shows how many messages there are in the array
    int lineCounter = 0;

    // This will tell the display the offset of where to show the message
    int lineOffset = 0;
    int loopCounter = 0;
    void init(void)
    {
        Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, false /*Serial Enable*/);
        pinMode(25, OUTPUT);
        digitalWrite(25, HIGH);
        Heltec.display->clear();
    }
    void echo(String message)
    {

        Heltec.display->clear();
        if (this->lineCounter <= 6)
        {
            // Put the new message in the array
            this->messages[this->lineCounter] = message;
            this->lineCounter = this->lineCounter + 1;

            // Move pointer to the next line

            for (int i = 0; i <= 6; i++)
            {
                Heltec.display->drawString(0, this->lineOffset, this->messages[i]);
                this->lineOffset = this->lineOffset + 9;
            }
        }
        else
        {
            // Move the messages 1 line higher then echo
            for (int i = 0; i <= 5; i++)
            {
                this->messages[i] = this->messages[i + 1];
                Heltec.display->drawString(0, this->lineOffset, this->messages[i]);
                this->lineOffset = this->lineOffset + 9;
            }

            // Set the last message then echo
            this->messages[6] = message;
            Heltec.display->drawString(0, this->lineOffset, this->messages[6]);
        }

        // Display the message
        Heltec.display->display();

        // Reset the pointers after displaying the message
        this->lineOffset = 0;
    }
        void clear(void) {
        this->messages[0] = "";
        this->messages[1] = "";
        this->messages[2] = "";
        this->messages[3] = "";
        this->messages[4] = "";
        this->messages[5] = "";
        this->messages[6] = "";
        this->messages[7] = "";
        this->lineCounter = 0;
        this->lineOffset = 0;
    }
};
