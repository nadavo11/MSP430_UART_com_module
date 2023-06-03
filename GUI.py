import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QPushButton, QSlider, QLabel, QVBoxLayout
from PyQt5.QtCore import Qt
from time import sleep

class GUI(QMainWindow):
    def __init__(self, s):
        super().__init__()

        self.s = s
        self.setWindowTitle("Modern GUI")
        self.setGeometry(100, 100, 400, 300)

        # Create the central widget
        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)

        # Create the layout for the central widget
        layout = QVBoxLayout(central_widget)

        # Create buttons
        button_names = [
            "Blink RGB LED",
            "Count up onto LCD",
            "Circular tone series",
            "Get delay time",
            "LDR 3-digit value",
            "Clear LCD screen",
            "Show menu",
            "Sleep"
        ]
        buttons = []
        for name in button_names:
            button = QPushButton(name)
            buttons.append(button)
            layout.addWidget(button)

        # Create the slider
        slider = QSlider(Qt.Horizontal)
        slider.setMinimum(100)
        slider.setMaximum(3000)
        slider.setValue(500)
        layout.addWidget(slider)

        # Create the label for the slider value
        self.slider_label = QLabel()
        layout.addWidget(self.slider_label)
        self.slider_label.setText(f"Delay Value: {500}")


        # Connect button click events to functions
        buttons[0].clicked.connect(self.blink_led)
        buttons[1].clicked.connect(self.count_up)
        buttons[2].clicked.connect(self.circular_tone)
        buttons[3].clicked.connect(lambda: self.get_delay_time(slider.value()))
        buttons[4].clicked.connect(self.ldr_value)
        buttons[5].clicked.connect(self.clear_lcd)
        buttons[6].clicked.connect(self.show_menu)
        buttons[7].clicked.connect(self.go_sleep)

        # Connect slider value change event to function
        slider.valueChanged.connect(self.slider_value_changed)

        # Set the stylesheet to make the background color black
        self.setStyleSheet("background-color: hsl(20, 20%, 5%); color: Aquamarine;")

    # Button click functions
    def blink_led(self):
        bytesChar = bytes('1', 'ascii')
        self.s.write(bytesChar)
        sleep(0.2)

    def count_up(self):
        bytesChar = bytes('2', 'ascii')
        self.s.write(bytesChar)
        sleep(0.2)

    def circular_tone(self):
        bytesChar = bytes('3', 'ascii')
        self.s.write(bytesChar)
        sleep(0.2)

    def get_delay_time(self, value):
        bytesChar = bytes('4', 'ascii')
        self.s.write(bytesChar)
        sleep(0.2)

        value = str(value) + '\0'
        value = bytes(value, 'ascii')
        print(f"Set delay time button clicked with value: {value}")
        s.write(bytesChar)

        sleep(0.5)


    def ldr_value(self):
        bytesChar = bytes('5', 'ascii')
        self.s.write(bytesChar)
        sleep(0.2)

    def clear_lcd(self):
        bytesChar = bytes('6', 'ascii')
        self.s.write(bytesChar)
        sleep(0.2)
    def show_menu(self):
        bytesChar = bytes('7', 'ascii')
        self.s.write(bytesChar)
        sleep(0.2)

    def go_sleep(self):
        bytesChar = bytes('8', 'ascii')
        self.s.write(bytesChar)
        sleep(0.2)

    def slider_value_changed(self, value):
        self.slider_label.setText(f"Delay Value: {value}")


if __name__ == '__main__':
    class Serial:
        def write(self, bytesChar):
            print(bytesChar)
    s = Serial()
    app = QApplication(sys.argv)
    window = GUI(s)
    window.show()
    sys.exit(app.exec_())