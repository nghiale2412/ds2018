/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package longestpath;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

/**
 *
 * @author long
 */
public class Map extends Mapper<LongWritable, Text, Text, IntWritable> {

    public void map(LongWritable key, Text value, Mapper.Context con) {
        
        String line = value.toString();
        String[] words = line.split("\n");
        
        for (String word : words) {
            //add key
            Text outputKey = new Text(word.toUpperCase().trim());
            //value
            IntWritable outputValue = new IntWritable(1);
            //generate output key/value
            try {                
                con.write(outputKey, outputValue);
            } catch (IOException | InterruptedException ex) {
                Logger.getLogger(Map.class.getName()).log(Level.SEVERE, null, ex);
            }

        }

    }

}
