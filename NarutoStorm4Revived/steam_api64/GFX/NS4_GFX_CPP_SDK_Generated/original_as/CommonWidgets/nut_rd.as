package script.result_net
{
   import flash.display.MovieClip;
   import script.net_cmn.smb_win2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol15")]
   public dynamic class nut_rd extends MovieClip
   {
      
      public var mc_ru_trophy:MovieClip;
      
      public var mc_rd_plate:MovieClip;
      
      public var txt_rd:MovieClip;
      
      public var mc_ru_win:smb_win2;
      
      public function nut_rd()
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

