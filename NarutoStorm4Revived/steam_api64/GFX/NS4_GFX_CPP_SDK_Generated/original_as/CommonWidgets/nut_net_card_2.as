package net_top_fla
{
   import flash.display.MovieClip;
   import script.net_card.nut_card;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class nut_net_card_2 extends MovieClip
   {
      
      public var all_card:nut_card;
      
      public function nut_net_card_2()
      {
         super();
         addFrameScript(5,this.frame6,10,this.frame11);
      }
      
      internal function frame6() : *
      {
         stop();
      }
      
      internal function frame11() : *
      {
         stop();
      }
   }
}

