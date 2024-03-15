import java.io.FileReader;
import java.io.IOException;
import java.io.StreamTokenizer;

public class Javatree
{
    public static void main(String[] args) throws Exception {
        try {/*from w  ww .  jav a  2s .co m*/

            FileReader rd = new FileReader("Javatree.java");
            StreamTokenizer st = new StreamTokenizer(rd);

            // Prepare the tokenizer for Java-style tokenizing rules
            st.parseNumbers();
            st.wordChars('_', '_');
            st.eolIsSignificant(true);

            // If whitespace is not to be discarded, make this call
            st.ordinaryChars(0, ' ');

            // These calls caused comments to be discarded
            st.slashSlashComments(true);
            st.slashStarComments(true);

            int token = st.nextToken();
            while (token != StreamTokenizer.TT_EOF) {

                token = st.nextToken();
                switch (token) {
                    
                // A number was found; the value is in nval
                case StreamTokenizer.TT_NUMBER:
                    double num = st.nval;
                    System.out.println(num);
                    break;
                
                // A word was found; the value is in sval
                case StreamTokenizer.TT_WORD:
                    String word = st.sval;
                    System.out.println(word);
                    break;

                // A double-quoted string was found; sval contains the contents
                case '"':
                    String dquoteVal = st.sval;
                    break;

                // A single-quoted string was found; sval contains the contents
                case '\'':
                    String squoteVal = st.sval;
                    break;

                // End of line character found
                case StreamTokenizer.TT_EOL:
                    break;

                // End of file has been reached
                case StreamTokenizer.TT_EOF:
                    break;
                
                // A regular character was found; the value is the token itself
                default:
                    char ch = (char) st.ttype;
                    break;
                }
            }
            rd.close();
        }
        catch (IOException e) {}
    }
}
