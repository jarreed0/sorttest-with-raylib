#include "raylib.h"
#include <chrono>
#include <iostream>
#include <vector>
//#include <algorithm>
#include <queue>
#include <functional>

#define SPRITE_WIDTH 70
#define SPRITE_HEIGHT 110
#define NUM_SPRITES 21

struct Sprite {
    Vector2 position;
    Rectangle sourceRect;
    bool horizontalDirection;
    bool verticalDirection;
};

// std::sort
void sort_sprites_with_sort(std::vector<Sprite>& sprites) {
    std::sort(sprites.begin(), sprites.end(), [](const Sprite& a, const Sprite& b) {
        return a.position.y + a.sourceRect.height < b.position.y + b.sourceRect.height;
    });
}

// std::stable_sort
void sort_sprites_with_stable(std::vector<Sprite>& sprites) {
    std::stable_sort(sprites.begin(), sprites.end(), [](const Sprite& a, const Sprite& b) {
        return a.position.y + a.sourceRect.height < b.position.y + b.sourceRect.height;
    });
}

// standard loop
void sort_sprites_with_loop(std::vector<Sprite>& sprites) {
    std::vector<Sprite> sorted_sprites;
    // Manually sort the vector by y-coordinate and save the result to the temporary vector
    while (!sprites.empty()) {
        // Find the sprite with the highest y-coordinate
        Sprite highest_y_sprite = sprites[0];
        size_t highest_y_index = 0;
        for (size_t i = 1; i < sprites.size(); ++i) {
            if (sprites[i].position.y + sprites[i].sourceRect.height < highest_y_sprite.position.y + highest_y_sprite.sourceRect.y) {
                highest_y_sprite = sprites[i];
                highest_y_index = i;
            }
        }
        // Move the highest y-coordinate sprite to the temporary vector
        sorted_sprites.push_back(std::move(highest_y_sprite));
        // Erase the highest y-coordinate sprite from the original vector
        sprites.erase(sprites.begin() + highest_y_index);
    }
    sprites = sorted_sprites;
}

// iterator
void sort_sprites_with_iterator(std::vector<Sprite>& sprites) {
    std::vector<Sprite> sorted_sprites;
    // Manually sort the vector by y-coordinate and save the result to the temporary vector
    while (!sprites.empty()) {
        // Find the sprite with the highest y-coordinate
        auto highest_y_sprite_iter = sprites.begin();
        for (auto it = sprites.begin(); it != sprites.end(); ++it) {
            if (it->position.y + it->sourceRect.height < highest_y_sprite_iter->position.y + highest_y_sprite_iter->sourceRect.height) {
                highest_y_sprite_iter = it;
            }
        }
        // Move the highest y-coordinate sprite to the temporary vector
        sorted_sprites.push_back(std::move(*highest_y_sprite_iter));
        // Erase the highest y-coordinate sprite from the original vector
        sprites.erase(highest_y_sprite_iter);
    }
    sprites = sorted_sprites;
}

// std::max_element
void sort_sprites_with_max(std::vector<Sprite>& sprites) {
    std::vector<Sprite> sorted_sprites;
    while (!sprites.empty()) {
        auto it = std::max_element(sprites.begin(), sprites.end(), [](const Sprite& a, const Sprite& b) {
            return a.position.y + a.sourceRect.height > b.position.y + b.sourceRect.height;
        });
        sorted_sprites.push_back(std::move(*it));
        sprites.erase(it);
    }
    sprites = sorted_sprites;
}

Sprite GenerateSprite(int row, int col) {
    Sprite sprite;
    sprite.position.x = static_cast<float>(GetRandomValue(SPRITE_WIDTH, GetScreenWidth() - SPRITE_WIDTH));
    sprite.position.y = static_cast<float>(GetRandomValue(SPRITE_HEIGHT, GetScreenHeight() - SPRITE_HEIGHT));
    sprite.sourceRect = (Rectangle) { static_cast<float>(SPRITE_WIDTH * col), static_cast<float>(SPRITE_HEIGHT * row), static_cast<float>(SPRITE_WIDTH), static_cast<float>(SPRITE_HEIGHT) };
    sprite.horizontalDirection = GetRandomValue(0, 1); // 0 = left, 1 = right
    sprite.verticalDirection = GetRandomValue(0, 1); // 0 = up, 1 = down
    return sprite;
}

int main(void) {
    // Initialize window and spritesheet texture
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Sprites Example");
    SetTargetFPS(60);
    Texture2D spritesheet = LoadTexture("sprites.png");

    // Generate random initial positions for each sprite and store in vector
    std::vector<Sprite> sprites;
    sprites.reserve(NUM_SPRITES);
    for (int i = 0; i < NUM_SPRITES; i++) {
        int row = i / 7;
        int col = i % 7;
        Sprite sprite = GenerateSprite(row, col);
        sprites.push_back(sprite);
    }
    for (int i = 0; i < 5000; i++) {
            Sprite sprite = GenerateSprite(GetRandomValue(0, 2), GetRandomValue(0, 6));
            sprites.push_back(sprite);
    }

    //for (const auto& s : sprites) { std::cout << "(" << s.position.x << ", " << s.position.y << ") ";} std::cout << std::endl << std::endl;
/*
    auto start_time = std::chrono::high_resolution_clock::now();
    sort_sprites_with_loop(sprites);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Solution 1 (for loop): " << duration.count() << " microseconds" << std::endl;
    //for (const auto& s : sprites) { std::cout << "(" << s.position.x << ", " << s.position.y << ") ";} std::cout << std::endl << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    sort_sprites_with_iterator(sprites);
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Solution 2 (iterator): " << duration.count() << " microseconds" << std::endl;
    //for (const auto& s : sprites) { std::cout << "(" << s.position.x << ", " << s.position.y << ") ";} std::cout << std::endl << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    sort_sprites_with_sort(sprites);
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Solution 3 (std::sort): " << duration.count() << " microseconds" << std::endl;
    //for (const auto& s : sprites) { std::cout << "(" << s.position.x << ", " << s.position.y << ") ";} std::cout << std::endl << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    sort_sprites_with_stable(sprites);
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Solution 4 (std::stable_sort): " << duration.count() << " microseconds" << std::endl;
    //for (const auto& s : sprites) { std::cout << "(" << s.position.x << ", " << s.position.y << ") ";} std::cout << std::endl << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    sort_sprites_with_max(sprites);
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Solution 5 (std::max_element): " << duration.count() << " microseconds" << std::endl;
    //for (const auto& s : sprites) { std::cout << "(" << s.position.x << ", " << s.position.y << ") ";} std::cout << std::endl << std::endl;

    CloseWindow();
*/
    // Render loop
    while (!WindowShouldClose())
    {
        // Check for new sprite creation on mouse click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Sprite sprite = GenerateSprite(GetRandomValue(0, 2), GetRandomValue(0, 6));
            sprite.position = GetMousePosition();
            sprites.push_back(sprite);
        }

        // Clear the screen
        BeginDrawing();
        ClearBackground((Color){2, 47, 64});
        //ClearBackground((Color){82, 208, 255});

        // Sort
        //sort_sprites_with_loop(sprites);
        //sort_sprites_with_iterator(sprites);
        //sort_sprites_with_sort(sprites);
        sort_sprites_with_stable(sprites);
        //sort_sprites_with_max(sprites);

        // Update and draw sprites
        for (auto& sprite : sprites)
        {
            // Update sprite position based on horizontal and vertical directions
            if (sprite.horizontalDirection) {
                sprite.position.x += 2;
                if (sprite.position.x + SPRITE_WIDTH > GetScreenWidth()) {
                    sprite.horizontalDirection = false;
                }
            }
            else {
                sprite.position.x -= 2;
                if (sprite.position.x < 0) {
                    sprite.horizontalDirection = true;
                }
            }

            if (sprite.verticalDirection) {
                sprite.position.y += 1;
                if (sprite.position.y + SPRITE_HEIGHT > GetScreenHeight()) {
                    sprite.verticalDirection = false;
                }
            }
            else {
                sprite.position.y -= 1;
                if (sprite.position.y < 0) {
                    sprite.verticalDirection = true;
                }
            }

            if(sprite.horizontalDirection) {
                DrawTextureRec(spritesheet, sprite.sourceRect, sprite.position, WHITE);
            } else {
                DrawTextureRec(spritesheet, (Rectangle){sprite.sourceRect.x, sprite.sourceRect.y, -sprite.sourceRect.width, sprite.sourceRect.height}, sprite.position, WHITE);
            }
        }

        // Draw current FPS
        DrawFPS(10, 10);

        EndDrawing();
    }

    // Cleanup
    UnloadTexture(spritesheet);
    CloseWindow();

    return 0;
}

