#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include "pch.hpp"

#include <exception>
#include <memory>

#include "Core/Drawable.hpp"

#include "Util/SpriteSheet.hpp"

/**
 * @class SpriteSheet
 * @brief Class representing an SpriteSheet animation with frames.
 */
class SpriteSheet final : public Core::Drawable {
public:
    /**
     * @brief Enum representing the state of the animation.
     */
    enum class State {
        PLAY,     /**< Animation is playing. */
        PAUSE,    /**< Animation is paused. */
        COOLDOWN, /**< Animation is COOLDOWN. */
        ENDED     /**< Animation is Ended(looping == false && Animate end.). */
    };

    /**
     * @brief Constructor for SpriteSheet class.
     * @param path file paths for the frames.
     * @param size size of the frame.
     * @param frames Frame indices.
     * @param play Whether the animation should play right away.
     * @param interval Interval between frames in milliseconds.
     * @param looping Whether the animation should loop.
     * @param cooldown Cooldown time in milliseconds before the animation can
     * restart.
     */
    SpriteSheet(
        const std::string               filepath,
        glm::vec2                       size,
        const std::vector<std::size_t>& frames,
        bool                            play,
        std::size_t                     interval,
        bool                            looping,
        std::size_t                     cooldown
    );

    /**
     * @brief Get the interval between frames.
     * @return Interval between frames in milliseconds.
     */
    std::size_t GetInterval() const { return m_Interval; }

    /**
     * @brief Check if the animation loops.
     * @return True if the animation loops, false otherwise.
     */
    bool GetLooping() const { return m_Looping; }

    /**
     * @brief Get the cooldown time.
     * @return Cooldown time in milliseconds.
     */
    std::size_t GetCooldown() const { return m_Cooldown; }

    /**
     * @brief Get the index of the current frame.
     * @return Index of the current frame.
     */
    std::size_t GetCurrentFrameIndex() const { return m_Index; }

    /**
     * @brief Get the total number of frames in the animation.
     * @return Total number of frames.
     */
    std::size_t GetFrameCount() const { return m_Frames.size(); }

    /**
     * @brief Get the current state of the animation
     * @return The current state of the animation
     */
    State GetState() const { return m_State; }

    /**
     * @brief Get the size of the current frame.
     * @return Size of the current frame.
     */
    glm::vec2 GetSize() const override { return m_FrameSize; }

    /**
     * @brief Set the interval between frames.
     * @param interval Interval between frames in milliseconds.
     */
    void SetInterval(int interval) { m_Interval = interval; }

    /**
     * @brief Set whether the animation loops.
     * @param looping True to enable looping, false to disable.
     */
    void SetLooping(bool looping) { m_Looping = looping; }

    /**
     * @brief Set the cooldown time.
     * @param cooldown Cooldown time in milliseconds.
     */
    void SetCooldown(int cooldown) { m_Cooldown = cooldown; }

    /**
     * @brief Set the current frame of the animation.
     * @param index Index of the frame to set as current.
     */
    void SetCurrentFrame(std::size_t index);

    /**
     * @brief Draw the current frame.
     * @param transform Transformation matrix for drawing.
     * @param zIndex Z-index for drawing.
     */
    void Draw(const Core::Matrices& data) override;

    /**
     * @brief Reset the animation to its initial frame.
     */
    void Reset() { SetCurrentFrame(0); }

    /**
     * @brief Start playing the animation.
     * If the animation is already playing, this method won't do anything.
     * If the animation has ended and `looping` is set to `false`, this would
     * replay the animation once.
     */
    void Play();

    /**
     * @brief Pause the animation.
     * If the animation has already been paused, this method won't do anything.
     */
    void Pause();

    /**
     * @brief Set draw range.
     *
     * @param displayRect The Rect of draw range
     */
    void SetDrawRect(const SDL_Rect displayRect);

    void SetFrames(const std::vector<std::size_t>& frames) {
        m_Frames = frames;
    }

    void SetAlpha(const Uint8 alpha);

    void SetColorMod(const SDL_Color& color);

private:
    /**
     * @brief Update the animation frames.
     */
    void Update();

private:
    /* Animation Part*/
    std::vector<std::size_t> m_Frames;
    State                    m_State;
    std::size_t              m_Interval;
    bool                     m_Looping;
    std::size_t              m_Cooldown;
    bool                     m_IsChangeFrame = false;

    unsigned long m_CooldownEndTime = 0;
    double        m_TimeBetweenFrameUpdate = 0;

    std::size_t m_Index = 0;

    /* SpriteSheet Part*/
    std::unique_ptr<Util::SpriteSheet> m_SpriteSheet;
    std::string                        m_Path;
    glm::vec2                          m_Size;
    std::size_t                        m_col;
    glm::vec2                          m_FrameSize;
};

#endif  // SPRITESHEET_HPP
