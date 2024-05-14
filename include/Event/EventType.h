#ifndef EVENT_TYPE_H
#define EVENT_TYPE_H

enum class EventType {
    ResetMap,
    DrawableUpdate,
    AttackPlayer,
    PlayerMove,
    EnemyMove,
    EnemyRemove,
};

#endif  // EVENT_TYPE_H
