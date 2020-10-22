#ifndef IRE_CORE_UTIL_UPDATABLE_PRIOTITY_QUEUE_H
#define IRE_CORE_UTIL_UPDATABLE_PRIOTITY_QUEUE_H

#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <tuple>
#include <cassert>

namespace ire::core::util {

    // based on Scapegoat Tree
    template <typename T, typename CompT = std::less<>>
    struct UpdatablePriorityQueue : private CompT
    {
        using ItemHandle = std::uint64_t;
        struct Item
        {
            template <typename... ArgsTs>
            Item(ItemHandle handle, ArgsTs&&... args) :
                handle(handle),
                value(std::forward<ArgsTs>(args)...)
            {
            }

            ItemHandle handle;
            T value;
        };

        UpdatablePriorityQueue() :
            m_nextUnusedHandle(0),
            m_removedItems{},
            m_items{},
            m_numItemsPoppedSinceLastOptimization(0)
        {
        }

        UpdatablePriorityQueue(const UpdatablePriorityQueue&) = default;
        UpdatablePriorityQueue(UpdatablePriorityQueue&&) = default;

        UpdatablePriorityQueue& operator=(const UpdatablePriorityQueue&) = default;
        UpdatablePriorityQueue& operator=(UpdatablePriorityQueue&&) = default;

        void reserve(std::size_t size)
        {
            m_items.reserve(size);
        }

        ItemHandle push(const T& value)
        {
            const auto id = nextId();

            m_items.emplace_back(id, value);
            std::push_heap(std::begin(m_items), std::end(m_items), comparator());

            maybeOptimize();

            return id;
        }

        ItemHandle push(T&& value)
        {
            const auto id = nextId();

            m_items.emplace_back(id, std::move(value));
            std::push_heap(std::begin(m_items), std::end(m_items), comparator());

            maybeOptimize();

            return id;
        }

        template <typename... ArgsTs>
        ItemHandle emplace(ArgsTs&&... args)
        {
            const auto id = nextId();

            m_items.emplace_back(
                id,
                std::forward<ArgsTs>(args)...
            );
            std::push_heap(std::begin(m_items), std::end(m_items), comparator());

            maybeOptimize();

            return id;
        }

        [[nodiscard]] const Item& top() const
        {
            popWhileFiltered();

            assert(!m_items.empty());

            return m_items.front();
        }

        [[nodiscard]] Item& top()
        {
            popWhileFiltered();

            assert(!m_items.empty());

            return m_items.front();
        }

        // pop should never do optimization, it doesn't make sense
        void pop()
        {
            popWhileFiltered();

            assert(!m_items.empty());

            popImpl();
        }

        [[nodiscard]] bool isEmpty()
        {
            popWhileFiltered();

            return m_items.empty();
        }

        [[nodiscard]] bool isEmpty() const
        {
            for (const auto& [id, value] : m_items)
            {
                if (m_removedItems.count(id) == 0)
                {
                    return true;
                }
            }

            return false;
        }

        void remove(ItemHandle id)
        {
            m_removedItems.emplace(id);

            maybeOptimize();
        }

    private:
        ItemHandle m_nextUnusedHandle;
        std::set<ItemHandle> m_removedItems;
        std::vector<Item> m_items;
        std::size_t m_numItemsPoppedSinceLastOptimization;

        [[nodiscard]] auto comparator() const
        { 
            return [cmp = static_cast<const CompT&>(*this)](const Item& lhs, const Item& rhs) {
                return cmp(lhs.value, rhs.value);
            };
        }

        [[nodiscard]] ItemHandle nextId()
        {
            return m_nextUnusedHandle++;
        }

        void maybeOptimize()
        {
            // We only want to trigger the update if the amount of 
            // work is justifiable. It should be fine to update
            // only if the number of removed items exceeds the number
            // of items in the queue, but it may be better
            // to change that condition in the future.
            if (m_removedItems.size() + m_numItemsPoppedSinceLastOptimization > m_items.size())
            {
                actuallyRemoveRemovedItems();

                m_numItemsPoppedSinceLastOptimization = 0;
            }
        }

        void popImpl()
        {
            std::pop_heap(std::begin(m_items), std::end(m_items), comparator());
            m_items.pop_back();

            m_numItemsPoppedSinceLastOptimization += 1;
        }

        void popWhileFiltered()
        {
            if (m_removedItems.empty())
            {
                return;
            }

            while (!m_items.empty())
            {
                const auto frontId = m_items.front().handle;

                auto it = m_removedItems.find(frontId);
                if (it == m_removedItems.end())
                {
                    break;
                }

                m_removedItems.erase(it);
                pop();
            }
        }

        void actuallyRemoveRemovedItems()
        {
            if (m_removedItems.empty())
            {
                return;
            }

            auto newLast = 
                std::remove_if(std::begin(m_items), std::end(m_items), [this](const Item& item) {
                    return m_removedItems.count(item.handle) != 0;
                });

            if (newLast != std::end(m_items))
            {
                m_items.erase(newLast, std::end(m_items));
                std::make_heap(std::begin(m_items), std::end(m_items), comparator());
            }

            m_removedItems.clear();
        }
    };
}

#endif // !IRE_CORE_UTIL_UPDATABLE_PRIOTITY_QUEUE_H
