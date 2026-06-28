package script.cutin_rcvry
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public class nut_recvry01 extends MovieClip
   {
      
      public var all_recvry_txt:nut_recvry_txt;
      
      public var dmy_gauge:MovieClip;
      
      public var mc_bonus_bg:MovieClip;
      
      public function nut_recvry01()
      {
         super();
         addFrameScript(15,this.frame16);
      }
      
      internal function frame16() : *
      {
         stop();
      }
   }
}

