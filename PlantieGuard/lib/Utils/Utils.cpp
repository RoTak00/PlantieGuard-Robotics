#include <Utils.h>

String generateUUID()
{
    String uuid = "";
    const char hexChars[] = "0123456789abcdef";

    for (int i = 0; i < 36; i++)
    {
        if (i == 8 || i == 13 || i == 18 || i == 23)
        {
            uuid += "-";
        }
        else if (i == 14)
        {
            uuid += "4"; // UUID version 4
        }
        else if (i == 19)
        {
            // UUID variant (8, 9, a, or b)
            uuid += hexChars[(random(8, 12))];
        }
        else
        {
            uuid += hexChars[random(0, 16)];
        }
    }

    return uuid;
}