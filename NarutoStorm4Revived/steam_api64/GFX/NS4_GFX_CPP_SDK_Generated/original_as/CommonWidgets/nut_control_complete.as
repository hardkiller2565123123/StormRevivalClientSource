package script.option_keyboard
{
   import flash.display.MovieClip;
   import script.icon_confirm.nut_conf_l;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public dynamic class nut_control_complete extends MovieClip
   {
      
      public var all_conf_m:nut_conf_l;
      
      public function nut_control_complete()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
      }
   }
}

