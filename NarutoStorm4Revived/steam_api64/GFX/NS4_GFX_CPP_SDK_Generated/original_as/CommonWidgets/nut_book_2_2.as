package net_bingo_rslt_fla
{
   import flash.display.MovieClip;
   import script.net_bingo_rslt.nut_book_data;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol37")]
   public dynamic class nut_book_2 extends MovieClip
   {
      
      public var mc_fade:MovieClip;
      
      public var mc_book_data02:nut_book_data;
      
      public var mc_book_data00:nut_book_data;
      
      public var mc_book_data01:nut_book_data;
      
      public function nut_book_2()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame2() : *
      {
         stop();
      }
      
      internal function frame3() : *
      {
         stop();
      }
   }
}

