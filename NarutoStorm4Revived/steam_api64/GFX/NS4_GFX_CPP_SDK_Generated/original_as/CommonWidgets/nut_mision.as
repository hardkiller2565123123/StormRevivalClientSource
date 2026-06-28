package script.info_mision
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class nut_mision extends MovieClip
   {
      
      public var mc_txt:MovieClip;
      
      public var mc_mark:MovieClip;
      
      public var mc_bg:MovieClip;
      
      public function nut_mision()
      {
         super();
         addFrameScript(19,this.frame20,29,this.frame30);
      }
      
      internal function frame20() : *
      {
         this.stop();
      }
      
      internal function frame30() : *
      {
         this.stop();
      }
   }
}

