import random
import copy
from reportlab.lib.pagesizes import letter
from reportlab.pdfgen import canvas

# Generate Sudoku Board

# Function to check if a grid is empty
def find_empty(grid):

    for i in range(9):
        for j in range(9):
            # If a spot on the grid is empty, return the indices
            if grid[i][j] == 0:
                return i, j
    return None

# Helper function to check if a value is in the correct position
def check_position(grid, value, position:tuple):

    row, column = position

    #verify number is not repeated in Rows or Columns

    if value in grid[row]: #check if the value is in the row
        return False
    if value in (grid[i][column] for i in range (9)): #check if value is in the column
        return False
    
    #Verify that number is not repeated within each subgrid
    X = column // 3
    Y = row // 3
    for i in range(Y * 3, (Y * 3) + 3):
        for j in range(X * 3, (X * 3) + 3):
            if grid[i][j] == value:
                return False
            
    return True

# Function to determine if a puzzle is solvable (Return True if Solvable, False if not)
def solvable(grid):
    # Find an empty space in the grid to start
    isEmpty = find_empty(grid) 
    # Base case, return True if no more empty spaces (puzzle is complete)
    if isEmpty == None:
        return True
    
    # Get row and column index for current empty space
    row, column = isEmpty

    vals = list(range(1,10))
    random.shuffle(vals)

    for val in vals:
        # if a number fits in the given spot, update the value in the grid
        if check_position(grid, val, (row, column)):
            grid[row][column] = val
            if solvable(grid):
                return True
            grid[row][column] = 0
    return False

# Function to generate a blank grid and fill it with the solvable function
def generate_board():
    grid = [[0] * 9 for i in range(9)]
    solvable(grid)
    return grid

# Check number of solutions for a given puzzle (Should only be 1 solution, but need to check after each number removed from a full grid)
def count_solutions(grid):
    empty = find_empty(grid)
    if empty == None:
        return 1
    row, column = empty

    count = 0
    for num in range(1, 10):
        if check_position(grid, num, (row, column)):
            grid[row][column] = num
            count += count_solutions(grid)
            if count > 1:
                break
            grid[row][column] = 0
    return count

# Generate puzzle by creating a full board, and removing X number of values
def generate_puzzle(removals):
    grid = generate_board()
    puzzle = copy.deepcopy(grid)

    remove_positions = [(r, c) for r in range(9) for c in range(9)]
    random.shuffle(remove_positions)

    removed = 0
    for r, c in remove_positions:
        if removed >= removals:
            break
        backup = puzzle[r][c]
        puzzle[r][c] = 0

        if count_solutions(copy.deepcopy(puzzle)) != 1:
            puzzle[r][c] = backup
        else:
            removed += 1

    return puzzle, grid

# Helper function to draw the grid, cell size specificed to 40 by default
def draw_sudoku_grid(c, start_x, start_y, cell_size=40):
    """Draws the 9×9 grid on the PDF."""
    for i in range(10):
        line_width = 2 if i % 3 == 0 else 1
        c.setLineWidth(line_width)

        # Horizontal line
        c.line(start_x, start_y + i * cell_size,
               start_x + 9 * cell_size, start_y + i * cell_size)

        # Vertical line
        c.line(start_x + i * cell_size, start_y,
               start_x + i * cell_size, start_y + 9 * cell_size)

# Helper function to add in the numbers in each cell
def draw_numbers(c, grid, start_x, start_y, cell_size=40, bold=False):
    """Draw puzzle numbers into the grid."""
    c.setFont("Helvetica-Bold" if bold else "Helvetica", 16)

    for r in range(9):
        for col in range(9):
            num = grid[r][col]
            if num != 0:
                x = start_x + col * cell_size + cell_size/2 - 4
                y = start_y + (8 - r) * cell_size + cell_size/2 - 6
                c.drawString(x, y, str(num))

# Function to export puzzle to pdf, puzzle on page 1 and solution on page 2
def export_to_pdf(puzzle, solution, filename="sudoku.pdf"):
    c = canvas.Canvas(filename, pagesize=letter)
    width, height = letter

    # Title
    c.setFont("Helvetica-Bold", 20)
    c.drawString(200, height - 50, "Sudoku Puzzle")

    # Puzzle grid
    draw_sudoku_grid(c, 100, height - 420)
    draw_numbers(c, puzzle, 100, height - 420, bold=True)

    # Solution (second page)
    c.showPage()
    c.setFont("Helvetica-Bold", 20)
    c.drawString(200, height - 50, "Sudoku Solution")

    draw_sudoku_grid(c, 100, height - 420)
    draw_numbers(c, solution, 100, height - 420)

    c.save()
    print(f"PDF saved as {filename}")

# Generate Puzzle & Export to PDF with solution
if __name__ == "__main__":
    puzzle, solution = generate_puzzle(removals=50)
    export_to_pdf(puzzle, solution, "sudoku.pdf")