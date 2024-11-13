#include <pch.h>

float getDistance(Vector3 v1, Vector3 v2)
{
    return std::sqrt(std::pow(v2.x - v1.x, 2) + std::pow(v2.y - v1.y, 2) + std::pow(v2.z - v1.z, 2));

}

int worldGetAllPeds(int arr_size, Actor* peds)
{
    Layout layout = GET_AMBIENT_LAYOUT();
    Iterator objectIterator = CREATE_OBJECT_ITERATOR(layout);
    Object currentObject = START_OBJECT_ITERATOR(objectIterator);
    int i = 0;
    while (i < arr_size and currentObject) {
        if (IS_ACTOR_HUMAN(currentObject))
        {
            peds[i] = currentObject;
            i++;
        }
        currentObject = OBJECT_ITERATOR_NEXT(objectIterator);
    }
    return i;
}