#ifndef WINDOW_H
#define WINDOW_H

namespace Display {
class Window {
public:
    struct UpdateData {};

    // init class window
    explicit Window();
    virtual ~Window() = default;

    //  about music
    void BeatHeart();

    void BeatIndicator();

    // about game

    void Update();

private:
};
}  // namespace Display

#endif  // WINDOW_H
