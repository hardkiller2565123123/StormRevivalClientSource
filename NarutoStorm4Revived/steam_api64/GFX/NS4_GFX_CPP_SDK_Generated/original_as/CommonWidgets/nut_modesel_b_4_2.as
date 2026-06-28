package modesel_fla
{
   import flash.display.MovieClip;
   import script.modesel_txt.nut_mode_txt;
   import script.modesel_txt.nut_modesel_txt;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol18")]
   public dynamic class nut_modesel_b_4 extends MovieClip
   {
      
      public var mc_cursor_u:MovieClip;
      
      public var mc_mode:nut_mode_txt;
      
      public var mc_modesel:nut_modesel_txt;
      
      public function nut_modesel_b_4()
      {
         super();
         addFrameScript(117,this.frame118,126,this.frame127);
      }
      
      internal function frame118() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame127() : *
      {
         this.stop();
      }
   }
}

