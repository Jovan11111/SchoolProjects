package projekat;

import java.awt.Button;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Label;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;

public class Main extends Frame {
    private Font labelFont = new Font("SansSerif", Font.BOLD, 16);
    private ProzorRad prozor;
    private ProzorText prozor1;
    
    public Main() throws IOException, InterruptedException {
        this.setTitle("RM2 projekat");
        
        // zelim da sve bude centrirano
        this.setLayout(new FlowLayout(FlowLayout.CENTER, 50, 10)); 

        // zelim da tekst bude malo veci i boldovan da lepse izgleda
        Label label1 = new Label("Dobrodošao u aplikaciju RM2 projekat!");
        label1.setFont(labelFont); 
        this.add(label1);

        Label label2 = new Label("Aplikacija radi Varijantu 7");
        label2.setFont(labelFont); 
        this.add(label2);

        Label label3 = new Label("Pritisni dugme za početak");
        label3.setFont(labelFont); 
        this.add(label3);

        // Ovo dugme zapocinje pravi rad aplikacije
        Button startButton = new Button("Počni rad");
        startButton.setFont(labelFont); 
        startButton.setBackground(new Color(159, 195, 233)); // Zelim da bude svetlo plavo
        
        startButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
				try {
	                dispose();
					prozor = new ProzorRad();
					prozor.startProveri();
					prozor.setVisible(true);
				} catch (IOException e) {
					e.printStackTrace();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
            }
        });

        startButton.setFocusable(false);
        startButton.setPreferredSize(new java.awt.Dimension(200, 50)); 

        this.add(startButton);

        // Dugme za pristup tekstu zadatka
        Button textButton = new Button("Tekst zadatka");
        textButton.setFont(labelFont);
        textButton.setBackground(new Color(159, 195, 233));

        textButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
				dispose();
				prozor1 = new ProzorText();
				prozor1.setVisible(true);
            }
        });
        textButton.setFocusable(false);
        textButton.setPreferredSize(new java.awt.Dimension(200, 50));
        
        this.add(textButton);
        
        
        this.setBackground(new Color(255, 237, 243)); // Pozadina roze

        this.setSize(400, 300); 
        this.setLocationRelativeTo(null); // Centrira sve

        // Osluskiavac za dugme X
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.out.println("Window closed");
                dispose();
            }
        });

    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Main main = new Main();
        main.setVisible(true);
    }
}
