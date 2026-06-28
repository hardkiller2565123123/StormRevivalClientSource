package script.net_bingo
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class smb_book extends MovieClip
   {
      
      public var nut_icon_cross:MovieClip;
      
      public function smb_book()
      {
         super();
         addFrameScript(0,this.frame1,6,this.frame7);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame7() : *
      {
         stop();
      }
   }
}

