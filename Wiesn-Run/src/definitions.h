#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//unsere Typdefinitionen jetzt mal in einer anderen Klasse
enum objectType {
    player, enemy, obstacle, shot
};
enum collisionType {
    stopping, contacting, travesable
}; // obstacles are stopping, enemies contacting and powerups are traversable
enum collisionDirection {
    fromLeft, fromRight, fromAbove, fromBelow
}; // the collisionDirection tells whether an enemy gets killed or whether we end up on top of an object


#endif // DEFINITIONS_H
