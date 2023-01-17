#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <algorithm>

const float FOV = 45.f;
const float SENSITIVITY = 0.1f;

class Controller {
  public:
    Controller()
        : front_(glm::vec3(0, 0, 0)), right_(glm::vec3(0, 0, 0)), up_(glm::vec3(0, 1, 0)),
          zoom_(FOV), first_click_(true){};

    void handle_mouse_button(const float &xpos, const float &ypos) {
        last_x_ = static_cast<float>(xpos);
        last_y_ = static_cast<float>(ypos);
    }

    void handle_mouse_movement(const float &xpos, const float &ypos) {
        if (first_click_) {
            last_x_ = xpos;
            last_y_ = ypos;
            first_click_ = false;
        }

        float xoffset = xpos - last_x_;
        float yoffset = last_y_ - ypos;
        last_x_ = xpos;
        last_y_ = ypos;

        xoffset *= SENSITIVITY;
        yoffset *= SENSITIVITY;

        yaw_ += xoffset;
        pitch_ += yoffset;

        pitch_ = std::min(pitch_, 89.f);
        pitch_ = std::max(pitch_, -89.f);

        front_.x = std::cos(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
        front_.y = std::sin(glm::radians(pitch_));
        front_.z = std::sin(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));

        front_ = glm::normalize(front_);
        right_ = glm::normalize(glm::cross(front_, glm::vec3(0, 1, 0)));
        up_ = glm::normalize(glm::cross(right_, front_));
    }

    void handle_mouse_scroll(const float &yoffset) {
        zoom_ -= yoffset;
        zoom_ = std::min(zoom_, 45.f);
        zoom_ = std::max(zoom_, 1.f);
    }

  public:
    glm::vec3 front_;
    glm::vec3 right_;
    glm::vec3 up_;

    float zoom_;

  private:
    bool first_click_;

    float last_x_;
    float last_y_;

    float pitch_;
    float yaw_;
};
#endif