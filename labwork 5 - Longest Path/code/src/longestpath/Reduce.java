/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package longestpath;

import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

/**
 *
 * @author long
 */
public class Reduce extends Reducer<Text, IntWritable, Text, IntWritable> {
    int tempMax = 0;
    Text longestPath = new Text();
    IntWritable max = null;
    public void reduce(Text word, Iterable<IntWritable> values, Reducer.Context con) throws IOException, InterruptedException {
        //add with value with same key
        for (IntWritable value : values) {
            if (value.get() > tempMax) {
                longestPath.set(word);
                tempMax = value.get();
            }
        }
        max = new IntWritable(tempMax);
    }

    @Override
    protected void cleanup(Context context) throws IOException, InterruptedException {
        context.write(longestPath, max);
    }
}
