#ifndef IRE_EVENTS_H
#define IRE_EVENTS_H

#include <SFML/Window/Event.hpp>

#include "core/time/Time.h"

#include <functional>
#include <type_traits>
#include <typeindex>
#include <utility>
#include <map>
#include <memory>
#include <cassert>

namespace ire::core::gui {

    struct RawEvent
    {
        TimePoint timestamp{};
        bool handled = false;
    };

    struct TranslatedEvent : RawEvent
    {
    };

    struct EventEmitter
    {
        struct AnyEventListener;

        using ListenerMapType = std::multimap<std::type_index, std::unique_ptr<AnyEventListener>>;
        using ListenerMapIterator = typename ListenerMapType::iterator;
        using EventType = std::type_index;

        struct AnyEventListener
        {
            AnyEventListener() = default;

            AnyEventListener(const AnyEventListener&) = delete;
            AnyEventListener(AnyEventListener&&) = delete;

            AnyEventListener& operator=(const AnyEventListener&) = delete;
            AnyEventListener& operator=(AnyEventListener&&) = delete;

            virtual ~AnyEventListener() = default;

            virtual void onEvent(void* typeErasedEvent) = 0;
        };

        template <typename EventT, typename FuncT>
        struct EventListener : AnyEventListener, private FuncT
        {
            static_assert(std::is_base_of_v<RawEvent, EventT>, "EventT must derive from Event");
            static_assert(
                std::is_same_v<
                    decltype(std::declval<FuncT>()(std::declval<EventT&>())),
                    void
                >, "Invalid event listener signature. Must be void(EventT&)");

            using EventType = EventT;

            template <typename T>
            EventListener(T&& func) :
                FuncT(std::forward<T>(func))
            {
            }

            void onEvent(void* typeErasedEvent) override
            {
                EventT& ev = *(reinterpret_cast<EventT*>(typeErasedEvent));
                FuncT::operator()(ev);
            }
        };

        struct EventListenerGuard
        {
            EventListenerGuard() :
                m_emitter(nullptr),
                m_iterator{}
            {
            }

            EventListenerGuard(EventEmitter& emitter, ListenerMapIterator it) :
                m_emitter(&emitter),
                m_iterator(it)
            {
            }

            EventListenerGuard(const EventListenerGuard&) = delete;
            EventListenerGuard(EventListenerGuard&& other) noexcept :
                m_emitter(other.m_emitter),
                m_iterator(other.m_iterator)
            {
                other.m_emitter = nullptr;
            }

            EventListenerGuard& operator=(const EventListenerGuard&) = delete;
            EventListenerGuard& operator=(EventListenerGuard&& other) noexcept
            {
                stopListening();

                m_emitter = other.m_emitter;
                m_iterator = other.m_iterator;

                other.m_emitter = nullptr;

                return *this;
            }

            void stopListening()
            {
                if (isListening())
                {
                    m_emitter->removeEventListener(m_iterator);
                    m_emitter = nullptr;
                }
            }

            [[nodiscard]] bool isListening() const
            {
                return m_emitter != nullptr;
            }

            ~EventListenerGuard()
            {
                stopListening();
            }

        private:
            EventEmitter* m_emitter;
            ListenerMapIterator m_iterator;
        };

        EventEmitter() = default;

        EventEmitter(const EventEmitter&) = delete;
        EventEmitter(EventEmitter&&) = delete;

        EventEmitter& operator=(const EventEmitter&) = delete;
        EventEmitter& operator=(EventEmitter&&) = delete;

        // The listener registered through this method will be kept
        // until the EventEmitter is destroyed. This means that
        // the references in the provided listener must outlive
        // the event emitter subscribed to.
        template <typename EventT, typename FuncT>
        void addEventListener(FuncT&& func)
        {
            using DecayedFuncT = std::remove_reference_t<FuncT>;
            using EventListenerType = EventListener<EventT, DecayedFuncT>;
            auto listener = std::make_unique<EventListenerType>(std::forward<FuncT>(func));
            auto type = eventType<EventT>();
            m_listeners.emplace(type, std::move(listener));
        }

        // The listener registered through this method will be kept until
        // the guard is destroyed or the used manually calls stopListening
        // on the guard object. The event emitter that is subscribed to
        // must be alive at the first call to stopListening.
        template <typename EventT, typename FuncT>
        [[nodiscard]] EventListenerGuard addTemporaryEventListener(FuncT&& func)
        {
            using DecayedFuncT = std::remove_reference_t<FuncT>;
            using EventListenerType = EventListener<EventT, DecayedFuncT>;
            auto listener = std::make_unique<EventListenerType>(std::forward<FuncT>(func));
            auto type = eventType<EventT>();
            auto it = m_listeners.emplace(type, std::move(listener));
            return EventListenerGuard(*this, it);
        }


    protected:

        template <typename EventT>
        void emitEvent(EventT& ev)
        {
            auto type = eventType<EventT>();
            auto [begin, end] = m_listeners.equal_range(type);
            while (begin != end && !ev.handled)
            {
                begin->second->onEvent(reinterpret_cast<void*>(&ev));
                ++begin;
            }
        }

        template <typename EventT>
        void emitEventIfNotHandled(EventT& ev)
        {
            if (!ev.handled)
            {
                emitEvent<EventT>(ev);
            }
        }

    private:
        ListenerMapType m_listeners;

        template <typename EventT>
        [[nodiscard]] static EventType eventType()
        {
            return std::type_index(typeid(EventT));
        }

        void removeEventListener(ListenerMapIterator it)
        {
            m_listeners.erase(it);
        }
    };

    struct WindowClosedEvent : RawEvent
    {
        bool cancel = false;
    };

    struct WindowResizedEvent : RawEvent
    {
        sf::Vector2f newSize;
    };

    struct WindowLostFocus : RawEvent
    {
    };

    struct WindowGainedFocus : RawEvent
    {
    };

    struct TextEnteredEvent : RawEvent
    {
        char32_t character;
    };

    struct KeyDownEvent : RawEvent
    {
        sf::Keyboard::Key key;
        bool alt;
        bool control;
        bool shift;
        bool system;
    };

    struct KeyUpEvent : RawEvent
    {
        sf::Keyboard::Key key;
        bool alt;
        bool control;
        bool shift;
        bool system;
    };

    struct MouseWheelScrolledEvent : RawEvent
    {
        sf::Mouse::Wheel wheel;
        float delta;
        sf::Vector2f position;
    };

    struct MouseButtonDownEvent : RawEvent
    {
        sf::Mouse::Button button;
        sf::Vector2f position;
    };

    struct MouseButtonUpEvent : RawEvent
    {
        sf::Mouse::Button button;
        sf::Vector2f position;
    };

    struct MouseMovedEvent : RawEvent
    {
        sf::Vector2f position;
    };

    struct MouseEnteredWindowEvent : RawEvent
    {
    };

    struct MouseLeftWindowEvent : RawEvent
    {
    };

    struct TouchBeganEvent : RawEvent
    {
        std::uint32_t finger;
        sf::Vector2f position;
    };

    struct TouchMovedEvent : RawEvent
    {
        std::uint32_t finger;
        sf::Vector2f position;
    };

    struct TouchEndedEvent : RawEvent
    {
        std::uint32_t finger;
        sf::Vector2f position;
    };

    struct ProgressBarValueChanged : TranslatedEvent
    {
        uint64_t value;
    };

}

#endif // !IRE_EVENTS_H
