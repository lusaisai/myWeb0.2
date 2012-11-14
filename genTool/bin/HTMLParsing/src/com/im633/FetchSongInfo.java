package com.im633;

import java.io.*;
import java.util.Scanner;
import org.jsoup.*;
import org.jsoup.nodes.*;

/**
 * This class reads a file which stores a list of songID from xiami.com
 * And output the song info
 * Input filename and output filename should be provided as arguments
 */

public class FetchSongInfo {
	private static final String srcURL="http://www.xiami.com/song/";
	private static final int TIMEOUT = 10000;
	private String inf;
	private String outf;
	
	public static void usage(int rcode) {
		System.out.println("Usage: java -cp \"/home/lusaisai/jars/jsoup-1.7.1.jar:.\" com.im633.FetchSongInfo <Input FileName> <Output FileName>");
		System.exit(rcode);
	}
	
	// The input file contains the song id list, the output file will have the song info
	public FetchSongInfo(String input, String output) {
		inf = input;
		outf = output;
	}
	
	public void fetchSong() throws IOException {
		Scanner scanner = new Scanner(new FileInputStream(inf));
		Writer out = new OutputStreamWriter(new FileOutputStream(outf));
		String url;
		String line;
		SongInfo si;
		int i = 1;
		
		while(scanner.hasNextLine()) {
			line = scanner.nextLine();
			url = srcURL + line;
			System.out.println(i + ": Parsing song id " + line);
			
			si = parseURL(url); //call parsing method
			si.setSongID(Long.parseLong(line)); // set the song id
			si.setLyric(si.getLyric().replaceAll("\r|\n", "")); //replace new lines
			out.write(si.toString());

			i++;
		}
		
		// File closing
		scanner.close();
		out.close();
	}
	
	public SongInfo parseURL(String url) throws IOException {
		SongInfo si = new SongInfo();
		
		try {
			Document doc = Jsoup.connect(url).userAgent("Mozilla").timeout(TIMEOUT).get();
			si.setTitle(doc.getElementById("title").child(0).html());
			si.setAlbum(doc.select("#albums_info a[href*=album]").first().html());
			si.setArtist(doc.select("#albums_info a[href*=artist]").first().html());
			si.setLyric(doc.getElementsByClass("lrc_main").first().html());
		} catch ( org.jsoup.HttpStatusException e ) {
			System.err.println("Looks like page is no longer there: " + url);
		} catch( java.net.SocketTimeoutException e ) {
			System.err.println("Timeout when connecting " + url);
		} catch ( Exception e ) {
			System.err.println("Cannot get enough info from url: " + url);
		} 
		
		return si;
	}
	
	
	public static void main(String[] args) throws IOException {
		if ( args.length != 2 ) {
			usage(1);
		}
		
		FetchSongInfo fsi = new FetchSongInfo(args[0], args[1]);
		fsi.fetchSong();
	}

}
