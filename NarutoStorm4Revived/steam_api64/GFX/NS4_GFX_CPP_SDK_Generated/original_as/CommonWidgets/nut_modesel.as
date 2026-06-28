package script.modesel
{
   import flash.display.MovieClip;
   import script.modesel_txt.nut_mode_txt;
   import script.modesel_txt.nut_modesel_txt;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class nut_modesel extends MovieClip
   {
      
      public var mc_cursor_u:MovieClip;
      
      public var mc_mode:nut_mode_txt;
      
      public var mc_modesel:nut_modesel_txt;
      
      public function nut_modesel()
      {
         super();
         addFrameScript(95,this.frame96,104,this.frame105);
      }
      
      internal function frame96() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame105() : *
      {
         this.stop();
      }
   }
}

