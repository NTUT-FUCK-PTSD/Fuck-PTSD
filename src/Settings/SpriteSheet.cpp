#include "SpriteSheet.hpp"

#include "Core/Texture.hpp"
#include "Core/TextureUtils.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

#include "Util/TransformUtils.hpp"

#include "config.hpp"

SpriteSheet::SpriteSheet(
    const std::string               filepath,
    glm::vec2                       frameSize,
    const std::vector<std::size_t>& frames,
    bool                            play,
    std::size_t                     interval,
    bool                            looping,
    std::size_t                     cooldown
)
    : m_Frames(frames),
      m_State(play ? State::PLAY : State::PAUSE),
      m_Interval(interval),
      m_Looping(looping),
      m_Cooldown(cooldown),
      m_Path(filepath),
      m_FrameSize(frameSize) {
    m_SpriteSheet = std::make_unique<Util::SpriteSheet>(filepath);
    m_Size = m_SpriteSheet->GetSize();
    m_col = static_cast<std::size_t>(m_Size.x / m_FrameSize.x);
}

void SpriteSheet::SetCurrentFrame(std::size_t index) {
    m_Index = index;
    if (m_State == State::ENDED || m_State == State::COOLDOWN) {
        /*this make sure if user setframe on ENDED/COOLDOWN, will play from
         * where you set the frame*/
        m_IsChangeFrame = true;
    }
}

void SpriteSheet::Draw(const Core::Matrices& data) {
    if (m_Index >= m_Frames.size()) { m_Index = 0; }
    SDL_Rect displayRect{
      static_cast<int>(m_FrameSize.x * (m_Frames[m_Index] % m_col)),
      static_cast<int>(m_FrameSize.y * (m_Frames[m_Index] / m_col)),
      static_cast<int>(m_FrameSize.x),
      static_cast<int>(m_FrameSize.y)
    };
    m_SpriteSheet->SetDrawRect(displayRect);
    m_SpriteSheet->Draw(data);

    Update();
}

void SpriteSheet::Play() {
    if (m_State == State::PLAY) return;
    if (m_State == State::ENDED || m_State == State::COOLDOWN) {
        m_Index = m_IsChangeFrame ? m_Index : 0;
        m_IsChangeFrame = false;
    }
    m_State = State::PLAY;
}

void SpriteSheet::Pause() {
    if (m_State == State::PLAY || m_State == State::COOLDOWN) {
        m_State = State::PAUSE;
    }
}

void SpriteSheet::Update() {
    unsigned long nowTime = Util::Time::GetElapsedTimeMs();
    if (m_State == State::PAUSE || m_State == State::ENDED) {
        LOG_TRACE("[ANI] is pause");
        return;
    }

    if (m_State == State::COOLDOWN) {
        if (nowTime >= m_CooldownEndTime) { Play(); }
        return;
    }

    m_TimeBetweenFrameUpdate += Util::Time::GetDeltaTimeMs();
    std::size_t updateFrameCount = static_cast<std::size_t>(
        m_TimeBetweenFrameUpdate / m_Interval
    );

    if (updateFrameCount <= 0) return;

    m_Index += updateFrameCount;
    m_TimeBetweenFrameUpdate = 0;

    std::size_t const totalFramesCount = m_Frames.size();
    if (m_Index >= totalFramesCount) {
        if (m_Looping) { m_CooldownEndTime = nowTime + m_Cooldown; }
        m_State = m_Looping ? State::COOLDOWN : State::ENDED;
        m_Index = m_Frames.size() - 1;
    }
}

void SpriteSheet::SetAlpha(const Uint8 alpha) {
    m_SpriteSheet->SetAlpha(alpha);
}

void SpriteSheet::SetColorMod(const SDL_Color& color) {
    m_SpriteSheet->SetColorMod(color);
}

void SpriteSheet::SetFrames(const std::vector<std::size_t>& frames) {
    m_Frames = frames;
    m_Index = 0;
    m_IsChangeFrame = true;
}
