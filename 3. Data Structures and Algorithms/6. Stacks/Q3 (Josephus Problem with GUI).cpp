#include "raylib.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

template <typename T> class CircularQueue
{
  private:
    T *arr;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

    void grow()
    {
        int newCapacity = capacity * 2;
        T *newArr = new T[newCapacity];

        for (int i = 0; i < count; i++)
        {
            newArr[i] = arr[(frontIndex + i) % capacity];
        }

        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = count - 1;
    }

    void shrink()
    {
        if (capacity <= 5)
        {
            return;
        }

        int newCapacity = capacity / 2;
        T *newArr = new T[newCapacity];

        for (int i = 0; i < count; i++)
        {
            newArr[i] = arr[(frontIndex + i) % capacity];
        }

        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = count - 1;
    }

    bool isHalf()
    {
        return count <= capacity / 2;
    }

  public:
    CircularQueue()
    {
        capacity = 5;
        arr = new T[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    void enqueue(T data)
    {
        if (count == capacity)
        {
            grow();
        }

        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = data;
        count++;
    }

    void dequeue()
    {
        if (count == 0)
        {
            return;
        }

        frontIndex = (frontIndex + 1) % capacity;
        count--;

        if (count == 0)
        {
            frontIndex = 0;
            rearIndex = -1;
        }

        if (isHalf())
        {
            shrink();
        }
    }

    T getFront()
    {
        if (count > 0)
        {
            return arr[frontIndex];
        }
        return T();
    }

    void clear()
    {
        count = 0;
        frontIndex = 0;
        rearIndex = -1;
    }

    void Load(int size)
    {
        clear();
        for (int i = 0; i < size; i++)
        {
            enqueue(i);
        }
    }

    // Get all current elements for visualization
    vector<T> getAllElements()
    {
        vector<T> elements;
        for (int i = 0; i < count; i++)
        {
            elements.push_back(arr[(frontIndex + i) % capacity]);
        }
        return elements;
    }

    // Rotate queue: move front element to rear
    void rotate()
    {
        if (count <= 1)
        {
            return;
        }

        T frontElement = arr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = frontElement;
    }

    // Modified JP for step-by-step visualization
    bool stepJP(int k, T &eliminated)
    {
        if (count == 0)
        {
            return false; // No more eliminations
        }

        if (count == 1)
        {
            eliminated = arr[frontIndex];
            clear();
            return false; // Last element eliminated
        }

        // Rotate k-1 times to get the element to eliminate at front
        for (int i = 0; i < k - 1; i++)
        {
            rotate();
        }

        // Eliminate the front element
        eliminated = arr[frontIndex];
        dequeue();

        return true; // More eliminations remaining
    }

    T getLastElement()
    {
        if (count > 0)
        {
            return arr[frontIndex];
        }
        return T();
    }

    bool isEmpty()
    {
        return count == 0;
    }

    int size()
    {
        return count;
    }

    ~CircularQueue()
    {
        delete[] arr;
    }
};

enum GameState
{
    SETUP,
    RUNNING,
    FINISHED
};

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "Josephus Problem Visualization");
    SetTargetFPS(60);

    CircularQueue<int> queue;

    int n = 10; // Number of people
    int k = 2;  // Count to eliminate
    int eliminated = -1;
    int winner = -1;

    GameState state = SETUP;
    bool waitingForInput = false; // Wait for user to press Enter

    char nInput[10] = "10";
    char kInput[10] = "2";
    bool editingN = false;
    bool editingK = false;

    while (!WindowShouldClose())
    {
        // Update
        if (state == SETUP)
        {
            // Handle input for n
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePos = GetMousePosition();
                Rectangle nBox = {350, 250, 300, 40};
                Rectangle kBox = {350, 320, 300, 40};

                editingN = CheckCollisionPointRec(mousePos, nBox);
                editingK = CheckCollisionPointRec(mousePos, kBox);
            }

            if (editingN)
            {
                int key = GetCharPressed();
                while (key > 0)
                {
                    if ((key >= 48) && (key <= 57) && (strlen(nInput) < 9))
                    {
                        int len = strlen(nInput);
                        nInput[len] = (char)key;
                        nInput[len + 1] = '\0';
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE) && strlen(nInput) > 0)
                {
                    nInput[strlen(nInput) - 1] = '\0';
                }
            }

            if (editingK)
            {
                int key = GetCharPressed();
                while (key > 0)
                {
                    if ((key >= 48) && (key <= 57) && (strlen(kInput) < 9))
                    {
                        int len = strlen(kInput);
                        kInput[len] = (char)key;
                        kInput[len + 1] = '\0';
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE) && strlen(kInput) > 0)
                {
                    kInput[strlen(kInput) - 1] = '\0';
                }
            }

            // Start button
            Rectangle startBtn = {400, 400, 200, 50};
            if (IsKeyPressed(KEY_ENTER) ||
                (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), startBtn)))
            {
                n = atoi(nInput);
                k = atoi(kInput);
                if (n > 0 && k > 0 && n <= 50)
                {
                    queue.Load(n);
                    state = RUNNING;
                    waitingForInput = true;
                    eliminated = -1;
                }
            }
        }
        else if (state == RUNNING)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                if (queue.size() > 1)
                {
                    bool hasMore = queue.stepJP(k, eliminated);
                    waitingForInput = true;

                    if (!hasMore || queue.size() == 1)
                    {
                        winner = queue.getLastElement();
                        state = FINISHED;
                        waitingForInput = false;
                    }
                }
                else
                {
                    winner = queue.getLastElement();
                    state = FINISHED;
                    waitingForInput = false;
                }
            }
        }
        else if (state == FINISHED)
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                state = SETUP;
                eliminated = -1;
                winner = -1;
                queue.clear();
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (state == SETUP)
        {
            DrawText("JOSEPHUS PROBLEM", 300, 100, 40, DARKBLUE);
            DrawText("Setup Parameters", 380, 180, 25, DARKGRAY);

            // N input
            DrawText("Number of People (n):", 350, 220, 20, BLACK);
            Rectangle nBox = {350, 250, 300, 40};
            DrawRectangleRec(nBox, editingN ? LIGHTGRAY : WHITE);
            DrawRectangleLinesEx(nBox, 2, editingN ? BLUE : DARKGRAY);
            DrawText(nInput, 360, 260, 20, BLACK);

            // K input
            DrawText("Elimination Count (k):", 350, 295, 20, BLACK);
            Rectangle kBox = {350, 320, 300, 40};
            DrawRectangleRec(kBox, editingK ? LIGHTGRAY : WHITE);
            DrawRectangleLinesEx(kBox, 2, editingK ? BLUE : DARKGRAY);
            DrawText(kInput, 360, 330, 20, BLACK);

            // Start button
            Rectangle startBtn = {400, 400, 200, 50};
            DrawRectangleRec(startBtn, DARKBLUE);
            DrawText("START", 460, 415, 20, WHITE);

            DrawText("Click fields to edit, then press START or ENTER", 270, 500, 18, GRAY);
        }
        else if (state == RUNNING || state == FINISHED)
        {
            DrawText("JOSEPHUS PROBLEM", 300, 30, 40, DARKBLUE);

            char info[100];
            sprintf(info, "Total: %d | Elimination Step: %d", n, k);
            DrawText(info, 320, 80, 20, DARKGRAY);

            // Draw circles in circular arrangement
            vector<int> elements = queue.getAllElements();
            int numElements = elements.size();

            if (numElements > 0)
            {
                float centerX = screenWidth / 2.0f;
                float centerY = screenHeight / 2.0f + 30;
                float radius = 200.0f;
                float circleRadius = 30.0f;

                for (int i = 0; i < numElements; i++)
                {
                    float angle = (2.0f * PI * i) / numElements - PI / 2;
                    float x = centerX + radius * cos(angle);
                    float y = centerY + radius * sin(angle);

                    Color color = BLUE;
                    if (state == FINISHED && elements[i] == winner)
                    {
                        color = GREEN;
                    }

                    DrawCircle(x, y, circleRadius, color);
                    DrawCircle(x, y, circleRadius - 3, LIGHTGRAY);

                    char numText[10];
                    sprintf(numText, "%d", elements[i]);
                    int textWidth = MeasureText(numText, 20);
                    DrawText(numText, x - textWidth / 2, y - 10, 20, BLACK);
                }
            }

            // Show elimination message
            if (eliminated >= 0 && state == RUNNING)
            {
                char elimMsg[100];
                sprintf(elimMsg, "Player %d eliminated!", eliminated);
                DrawText(elimMsg, 360, 615, 25, RED);
            }

            // Show instruction to press Enter
            if (state == RUNNING)
            {
                DrawText("Press ENTER to eliminate next player", 300, 650, 20, DARKBLUE);
            }

            // Show winner
            if (state == FINISHED)
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));

                char winMsg[100];
                sprintf(winMsg, "WINNER: Player %d", winner);
                int msgWidth = MeasureText(winMsg, 50);
                DrawText(winMsg, (screenWidth - msgWidth) / 2, 280, 50, GREEN);

                DrawText("Press SPACE to restart", 350, 380, 25, WHITE);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}