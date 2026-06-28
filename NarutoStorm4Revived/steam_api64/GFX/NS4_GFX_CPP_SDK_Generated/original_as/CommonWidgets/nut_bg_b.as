package script.result_main
{
   import flash.display.MovieClip;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public class nut_bg_b extends MovieClip
   {
      
      public var dmy_bg:nut_tex00;
      
      public function nut_bg_b()
      {
         super();
         addFrameScript(19,this.frame20,59,this.frame60);
      }
      
      internal function frame20() : *
      {
         this.stop();
      }
      
      internal function frame60() : *
      {
         this.stop();
      }
   }
}

