#include <pch.h>

float getDistanceBetweenCoords(Vector3 v1, Vector3 v2)
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

const char* toConstChar(int number) {
    // Static buffer for storing the formatted integer
    static char buffer[20];

    // Format the integer into the buffer
    snprintf(buffer, sizeof(buffer), "%d", number);

    return buffer;
}

const char* toConstChar(float number) {
    // Static buffer for storing the formatted float
    static char buffer[20];

    // Format the float with two decimal places into the buffer
    snprintf(buffer, sizeof(buffer), "%.2f", number);  // Adjust precision as needed

    return buffer;
}

const char* toConstChar(const Vector3& vector) {
    // Static buffer to hold the formatted string
    static char buffer[100];

    // Format the Vector3 values into the buffer
    snprintf(buffer, sizeof(buffer), "[%.2f, %.2f, %.2f]", vector.x, vector.y, vector.z);

    return buffer;
}

const char* concatCharArr(int count, ...) {
    // Define a maximum buffer size (adjust based on your requirements)
    const size_t BUFFER_SIZE = 1024;

    // Allocate a buffer for the result
    char* result = new char[BUFFER_SIZE];
    result[0] = '\0'; // Initialize the buffer as an empty string

    // Initialize the variable argument list
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        const char* str = va_arg(args, const char*);

        // Concatenate the current string into the result buffer
        errno_t err = strcat_s(result, BUFFER_SIZE, str);
        if (err != 0) {
            std::cerr << "String concatenation failed!" << std::endl;
            delete[] result;
            va_end(args);
            return nullptr; // Return null on failure
        }
    }

    va_end(args);
    return result; // Return the concatenated result
}



float dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 normalize(Vector3 vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    return { vector.x / length, vector.y / length, vector.z / length };
}

Vector3 getCameraRightVector(Vector3 forwardvector)
{
    Vector3 worldUp = { 0.0f, 0.0f, 1.0f };
    return normalize(Vector3::Cross(worldUp, forwardvector));
}

Vector3 getCameraUpVector(Vector3 forwardvector, Vector3 rightvector)
{
    return normalize(Vector3::Cross(forwardvector, rightvector));
}

Vector2 worldToScreen(const Vector3& entityPos, int screenWidth, int screenHeight) {

    Camera _Camera = GET_GAME_CAMERA();
    const Vector3 cameraPos = GET_CAMERA_POSITION(_Camera);
    const Vector3 cameraForward = GET_CAMERA_DIRECTION(_Camera);
    const Vector3 cameraRight = getCameraRightVector(cameraForward);
    const Vector3 cameraUp = getCameraUpVector(cameraForward, cameraRight);
    const float fov = GET_CAMERA_FOV(_Camera);
    const float aspectRatio = GET_CAMERA_ASPECT_RATIO(_Camera);


    // Step 1: Vector from camera to entity
    Vector3 cameraToEntity = entityPos - cameraPos;

    // Step 2: Transform to camera space
    float xCameraSpace = dot(cameraToEntity, cameraRight);
    float yCameraSpace = dot(cameraToEntity, cameraUp);
    float zCameraSpace = dot(cameraToEntity, cameraForward);

    // Step 3: Perspective projection
    float fovFactor = tan(fov / 2.0f);
    float screenX = (xCameraSpace / (zCameraSpace * fovFactor)) * aspectRatio;
    float screenY = (yCameraSpace / (zCameraSpace * fovFactor));

    // Step 4: Convert to screen coordinates
    float pixelX = (screenX + 1.0f) * 0.5f;
    float pixelY = (1.0f + screenY) * 0.5f;

    return Vector2{ pixelX, pixelY };
}