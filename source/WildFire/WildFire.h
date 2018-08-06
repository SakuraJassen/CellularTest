#pragma once

#include <optional>
#include <vector>
#include <array>
#include <memory>
#include <unordered_set>

#include "../CellularAutomaton.h"

//class InputMode;

class WildFire : public CellularAutomaton
{
    std::vector<sf::Color> m_cellColor;
    public:
        enum class CellType
        {
            Dirt,
            Tree,
            Fire,
        };

        struct Cell
        {
            CellType m_ct;
            uint m_life;
        };

        struct CellPointInfo
        {
            int x;
            int y;
            int index;
            Cell* cell;
        };

    public:
        WildFire(const Config& config, const App& app);

        void input(const sf::Event& e) override;
        void update() override;

        const Config& getConfig() const;
        CellPointInfo getCellPointInfo(const sf::Vector2i& cellPoint);

        void setCell(unsigned x, unsigned y, Cell cell);
        void setCell(unsigned x, unsigned y, CellType celltype);
        Cell getCell(int x, int y);

        void updateCellColor(unsigned x, unsigned y);
    private:
        std::optional<sf::Vector2i> getMouseInputPosition() const;
        void onRenderCells(sf::RenderWindow& window) override;

        //std::unique_ptr<InputMode> m_inputMode;
        std::vector<Cell> m_cells;
        bool canGrow;
        bool canBurn;
        bool m_isInEditMode = true;
};
