package script.hist_cmn_brt
{
   import Enum.Enum;
   import KeyHelp.KeyHelpCode;
   
   public class HistKeyHelpManager
   {
      
      public static const CCD_EPISODE_SELECT:int = Enum.Next(0);
      
      public static const CCD_CHAPTER_SELECT:int = Enum.Next();
      
      public static const CCD_CHAPTER_SELECT_BONUS:int = Enum.Next();
      
      public static const CCD_OUTLINE_WINDOW:int = Enum.Next();
      
      public static const CCD_RELEASE_WINDOW:int = Enum.Next();
      
      public static const CCD_COMPLETE_WINDOW:int = Enum.Next();
      
      private var m_keyHelp:KeyHelpCode = new KeyHelpCode();
      
      private var m_isPushed:Boolean;
      
      private var m_type:int;
      
      private var m_isSkipBack:Boolean;
      
      private var m_isSkipNext:Boolean;
      
      private var m_isSkipUpdate:Boolean;
      
      public function HistKeyHelpManager()
      {
         super();
         this.m_isPushed = false;
         this.m_type = -1;
         this.m_isSkipBack = false;
         this.m_isSkipNext = false;
         this.m_isSkipUpdate = false;
      }
      
      public function DeleteKeyHelp() : *
      {
         if(Boolean(this.m_keyHelp) && this.m_isPushed == true)
         {
            this.m_isPushed = false;
            this.m_type = -1;
            this.m_keyHelp.PopKeyHelp();
         }
      }
      
      public function SetSkipInfo(param1:Boolean, param2:Boolean) : *
      {
         if(this.m_isSkipBack != param1 || this.m_isSkipNext != param2)
         {
            this.m_isSkipUpdate = true;
         }
         this.m_isSkipBack = param1;
         this.m_isSkipNext = param2;
      }
      
      public function CreateKeyHelp(param1:int) : *
      {
         if(this.m_type == param1 && this.m_isSkipUpdate == false)
         {
            return;
         }
         this.m_isSkipUpdate = false;
         if(this.m_keyHelp)
         {
            if(this.m_isPushed == true)
            {
               this.m_isPushed = false;
               this.m_keyHelp.PopKeyHelp();
            }
            this.m_type = param1;
            switch(this.m_type)
            {
               case CCD_EPISODE_SELECT:
                  if(this.m_isSkipBack)
                  {
                     this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_L1,"advMainMenu_012");
                  }
                  if(this.m_isSkipNext)
                  {
                     this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R1,"advMainMenu_013");
                  }
                  this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_START,"item_list_000");
                  this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R_LEFT,"advMainMenu_006");
                  this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
                  this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
                  this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_L2 + " " + KeyHelpCode.CCD_BTN_ICON_R2,"eventcheck_008");
                  break;
               case CCD_CHAPTER_SELECT:
                  this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_START,"item_list_000");
                  this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R_LEFT,"advMainMenu_006");
                  this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
                  this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
                  break;
               case CCD_CHAPTER_SELECT_BONUS:
                  this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_START,"item_list_000");
                  this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R_UP,"battlestartmenu_096");
                  this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R_LEFT,"advMainMenu_006");
                  this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
                  this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
                  break;
               case CCD_OUTLINE_WINDOW:
                  this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_CLOSE2);
                  break;
               case CCD_RELEASE_WINDOW:
                  this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_NEXT);
                  break;
               case CCD_COMPLETE_WINDOW:
                  this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_OK);
            }
            if(this.m_isPushed == false)
            {
               this.m_isPushed = true;
               this.m_keyHelp.PushKeyHelp();
            }
         }
      }
      
      public function IsKeyHelpCreated() : Boolean
      {
         return this.m_isPushed;
      }
   }
}

