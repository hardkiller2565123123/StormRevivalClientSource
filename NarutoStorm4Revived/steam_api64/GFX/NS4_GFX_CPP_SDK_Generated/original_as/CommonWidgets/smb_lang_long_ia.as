package script.duel_act_lang
{
   import flash.display.MovieClip;
   import script.xcmn_btn_plat.all_btn_plat;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol30")]
   public class smb_lang_long_ia extends MovieClip
   {
      
      public var mc_btn:all_btn_plat;
      
      public function smb_lang_long_ia()
      {
         super();
         mc_btn.SetButtonId(all_btn_plat.CCD_BUTTON_STK_L3);
      }
   }
}

