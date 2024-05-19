#include <iostream>
#include <unordered_map>
#include <chrono>

std::unordered_map<std::string, std::chrono::steady_clock::time_point> requestMap;
const int REQUEST_LIMIT = 10; // Limitele de solicitare IP
const int TIME_LIMIT = 10; // Limită de timp în secunde

bool isAllowedRequest(const std::string& ipAddress) {
    auto currentTime = std::chrono::steady_clock::now();
    
    if (requestMap.find(ipAddress) == requestMap.end()) {
        requestMap[ipAddress] = currentTime;
        return true;
    } else {
        auto lastRequestTime = requestMap[ipAddress];
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastRequestTime).count() < TIME_LIMIT) {
            if (requestMap.size() >= REQUEST_LIMIT) {
                return false; // Limita de solicitare a fost depășită
            }
        }
        requestMap[ipAddress] = currentTime;
        return true;
    }
}

int main() {
    std::string ipAddress = "192.168.1.1";
    
    for (int i = 0; i < 15; i++) {
        if (isAllowedRequest(ipAddress)) {
            std::cout << "Cerere de la " << ipAddress << " permis." << std::endl;
        } else {
            std::cout << "Cerere de la " << ipAddress << " blocat din cauza limitării ratei." << std::endl;
        }
    }

    return 0;
}
