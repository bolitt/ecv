package com.ec.command
{
	import flash.external.*;
	import flash.system.*;
	import com.ec.log.Logger;
	import com.ec.app.EditPlayer;
	
	public class CommandDispatcher
	{
		private var _logger:Logger = null;
		private var _proxy:CommandProxy = null;
		
		public function CommandDispatcher(editPlayer:EditPlayer)
		{
			_logger = Logger.getInstance("CommandDispatcher");
			_proxy = new CommandProxy(editPlayer);
		}
		
		protected function initializeBinding():void
		{
			ExternalInterface.marshallExceptions = true;
			const bindingName:String = "slave";
			ExternalInterface.addCallback(bindingName, bindingCallback);
			_logger.debug("binded");
		}
		
		protected function bindingCallback(command:String, ...parameters): Boolean 
		{
			try {
				_logger.debug(command + "|" + parameters.join("&"));
				_proxy.invoke(command, parameters);
			} catch (e:Error) {
				_logger.error(e.toString());
				return false;
			}
			return true;
		}
		
		protected function enableAllowDomain():void
		{
			_logger.debug("enableAllowDomain");
			Security.allowDomain('*');
		}
		public function bind(): void
		{
			_logger.debug("bind");
			enableAllowDomain();
			
			if (ExternalInterface.available) {
				try {
					initializeBinding();
				} catch (error:SecurityError) {
					_logger.error("A SecurityError occurred: " + error.message + "\n");
				} catch (error:Error) {
					_logger.error("An Error occurred: " + error.message + "\n");
				}
			} else {
				_logger.info("External interface is not available for this container.")
			}
		}
		
		
		
	}
}