#pragma once
#include <string>

namespace GameNotificationService
{
    typedef struct Notification {       
        std::string content;
    
        Notification() {
            content = "";
        }

        Notification(std::string _content) {
            content = _content;
        }
    } Notification;

    void SendNotification(Notification notification);
    void Speak(Notification notification);
};

