package org.net9.tt
{
	import flash.events.*;
	import flash.net.*;
	import flash.utils.ByteArray;
	import flash.utils.Dictionary;
	import flash.xml.*;
	
	import mx.utils.StringUtil;
	import mx.utils.URLUtil;
	
	import nochump.util.zip.*;
	
	import org.osmf.utils.URL;
	
	[Event(name=Event.COMPLETE, type=Event.COMPLETE)]
	public class Loader extends EventDispatcher
	{
		public static const COMPLETE_EVENT:String = Event.COMPLETE;
		private var completeEvent:Event = new Event(Event.COMPLETE);
		
		private var _fileDict:Dictionary = new Dictionary();
		private var _entries:Array = null;
		private var _zipFile:ZipFile = null;
		private var _manifect:Manifect = null;
		
		
		public function get fileDict():Dictionary
		{
			return _fileDict;
		}
		public function set fileDict(value:Dictionary):void
		{
			_fileDict = value;
		}
		public function get entries():Array
		{
			return _entries;
		}
		public function set entries(value:Array):void
		{
			_entries = value;
		}
		public function get zipFile():ZipFile
		{
			return _zipFile;
		}

		public function set zipFile(value:ZipFile):void
		{
			_zipFile = value;
		}

		public function get manifect():Manifect
		{
			return _manifect;
		}
		public function set manifect(value:Manifect):void
		{
			_manifect = value;
		}
		

		
		public var log:Function = trace; 
		
		public function Loader()
		{
		}
		
		public function Load(path:String) : void 
		{
			var request:URLRequest = new URLRequest(path);
			var loader:URLLoader = new URLLoader();
			loader.dataFormat = URLLoaderDataFormat.BINARY;
			loader.addEventListener(Event.COMPLETE, completedHandler);
		
			try {
				log("to load");
				loader.load(request);
				log("loading");
			}
			catch (error:SecurityError)
			{
				log("A SecurityError has occurred.");
			}
		}	
		
		private function completedHandler(event:Event):void
		{
			log("completedHandler");
			var loader:URLLoader = URLLoader(event.target);
			//log("bytesTotal:" + loader.bytesTotal);
			//log("bytesLoaded:" + loader.bytesLoaded);
			readZip(loader.data, loader.dataFormat);
			//log(loader.data);
		}
		
		private function readZip(data:*, dataFormat:String):void
		{
			/*
			log("dataFormat: " + dataFormat);
			log("constructor: " + data.constructor);
			log("is ByteArray: " + (data is ByteArray));
			log("is String: " + (data is String));
			log("typeof: " + (typeof data));
			*/
			var zipFile:ZipFile = new ZipFile(data);
			readFile(zipFile);
		}
		
		private function readFile(zipFile:ZipFile):void
		{
			var entries:Array = zipFile.entries;
			_entries = entries;
			_zipFile = zipFile;
			
			for (var i:int = 0; i < entries.length; i++)
			{
				var entry:ZipEntry = entries[i] as ZipEntry;
				var entryBytes:ByteArray = zipFile.getInput(entry);
				_fileDict[entry.name] = entryBytes;
				if (entry.isDirectory()) {
					/*
					log(entry.name + ":dir|" 
						  + "size:" + entry.compressedSize + "/" + entry.size+"|"
						  + "time:" + entry.time + "|"
						  + "method:" + entry.method + "|"
						  + "comment:" + entry.comment + "|"
						  + "extra:" + entry.extra + "|"
						  + "crc:" + entry.crc);
					*/
				} else {
					/*
					log(entry.name + ":file|" 
						+ "size:" + entry.compressedSize + "/" + entry.size+"|"
						+ "time:" + entry.time + "|"
						+ "method:" + entry.method + "|"
						+ "comment:" + entry.comment + "|"
						+ "extra:" + entry.extra + "|"
						+ "crc:" + entry.crc);
					*/
					var regex:RegExp = /manifect.xml$/i;  // case-insensitive 
					if (entry.name.match(regex)) {
						readManifect(entryBytes, entry.name);
					}
				}
			}
			dispatchEvent(completeEvent);
		}
		
		private function readManifect(manifect:ByteArray, path:String):void {	
			var pos:int = path.lastIndexOf("/");
			var basepath:String = path.substr(0, pos + 1);
			
			var str:String = manifect.readMultiByte(manifect.length, "utf-8");
			//log(str);
			var xml:XML = new XML(str);
			//log(xml.toString());
			//log(xml.toXMLString());
			
			var version:XML = xml..Version[0];
			//log(version);
			var copyright:XML = xml..Copyright[0];
			//log(copyright);
			var author:XML = xml..Author[0];
			//log(author);
			var createTime:XML = xml..CreateTime[0];
			//log(createTime);
			var clip:XMLList = xml..Clip;
			//log(clip);
			
			_manifect = new Manifect();
			_manifect.version = version;
			_manifect.copyright = copyright;
			_manifect.author = author;
			_manifect.createTime = createTime;
			
			for each (var image:XML in clip.Image) {
				//log(image.Name + "|" + image.Row + "|" + image.Column);
				var i:IndexedImage = new IndexedImage();
				i.name = image.Name;
				i.row = image.Row;
				i.column = image.Column;
				i.data = _fileDict[basepath + i.name];
				
				log(i.name + "|" 
					+ i.row + "|" 
					+ i.column + "|"
					+ i.data.length);
				
				_manifect.clip.push(i);
			}
		}
	}
}