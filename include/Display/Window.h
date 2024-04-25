#ifndef WINDOW_H
#define WINDOW_H

namespace Display {
class Window {
public:
    // init class window
    explicit Window();
    virtual ~Window() = default;

    //  about music
    static void BeatHeart();

    static void BeatIndicator();

    void Update();

private:
};
}  // namespace Display

#endif  // WINDOW_H
