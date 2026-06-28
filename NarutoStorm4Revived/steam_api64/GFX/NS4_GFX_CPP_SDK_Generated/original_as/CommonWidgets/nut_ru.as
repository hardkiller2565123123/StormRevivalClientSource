package script.result_net
{
   import flash.display.MovieClip;
   import script.net_cmn.smb_win2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol12")]
   public dynamic class nut_ru extends MovieClip
   {
      
      public var mc_ru_trophy:MovieClip;
      
      public var txt_ru:MovieClip;
      
      public var mc_ru_plate:MovieClip;
      
      public var mc_ru_win:smb_win2;
      
      public function nut_ru()
      {
         super();
         addFrameScript(7,this.frame8,14,this.frame15);
      }
      
      internal function frame8() : *
      {
         stop();
      }
      
      internal function frame15() : *
      {
         stop();
      }
   }
}

