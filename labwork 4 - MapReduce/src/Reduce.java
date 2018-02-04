
import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author long
 */
public class Reduce extends Reducer<Text, IntWritable, Text, IntWritable> {
    
    public void reduce(Text word, Iterable<IntWritable> values, Reducer.Context con) throws IOException, InterruptedException {
        //initiaze count
        int sum = 0;
        //add with value with same key
        for (IntWritable value : values) {
            sum += value.get();
        }
        //generate new result after reduce
        con.write(word, new IntWritable(sum));

    }

}
