package script.shop_cmn
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public class nut_help extends MovieClip
   {
      
      public var txt_help:MovieClip;
      
      public function nut_help()
      {
         super();
         addFrameScript(5,this.frame6,10,this.frame11);
      }
      
      internal function frame6() : *
      {
         this.stop();
      }
      
      internal function frame11() : *
      {
         this.stop();
      }
   }
}

