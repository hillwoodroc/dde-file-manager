#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <QPushButton>

#include "views/historystack.h"
#include "views/dfilemanagerwindow.h"
#define private public
#include "views/dtoolbar.h"

TEST(DToolBarTest,init)
{
    DToolBar w;
    EXPECT_NE(nullptr,w.m_addressToolBar);
    EXPECT_NE(nullptr,w.m_backButton);
    EXPECT_NE(nullptr,w.m_forwardButton);
    EXPECT_NE(nullptr,w.m_searchButton);
    EXPECT_NE(nullptr,w.m_detailButton);
    EXPECT_NE(nullptr,w.m_contollerToolBar);
    EXPECT_NE(nullptr,w.m_contollerToolBarContentLayout);
    EXPECT_NE(nullptr,w.m_crumbWidget);
}

TEST(DToolBarTest,get_crumb_widget)
{
    DToolBar w;
    EXPECT_EQ(w.getCrumbWidget(),w.m_crumbWidget);
}

TEST(DToolBarTest,add_history_stack)
{
    DToolBar w;
    int org = w.m_navStacks.size();
    w.addHistoryStack();
    EXPECT_EQ(org + 1,w.m_navStacks.size());
}

TEST(DToolBarTest,remove_navStack)
{
    DToolBar w;
    w.addHistoryStack();
    w.addHistoryStack();
    w.removeNavStackAt(1);
    EXPECT_EQ(1,w.m_navStacks.size());
    w.switchHistoryStack(0);
}

TEST(DToolBarTest,switch_navStack)
{
    DToolBar w;
    w.addHistoryStack();
    w.addHistoryStack();
    w.switchHistoryStack(1);
    EXPECT_EQ(2,w.m_navStacks.size());
}

TEST(DToolBarTest,nav_stack_count)
{
    DToolBar w;
    EXPECT_EQ(w.m_navStacks.size(),w.navStackCount());
    w.addHistoryStack();
    EXPECT_EQ(w.m_navStacks.size(),w.navStackCount());
}

TEST(DToolBarTest,set_custom_action_list)
{
    DToolBar w;
    QAction ac("test");
    bool ok = false;
    QEventLoop loop;
    QObject::connect(&ac,&QAction::triggered,&ac,[&ok,&loop](){
        ok = true;
        loop.exit();
    },Qt::QueuedConnection);
    w.setCustomActionList({&ac});
    ASSERT_EQ(1,w.m_actionList.size());
    ASSERT_EQ(&ac, w.m_actionList.at(0));

    w.triggerActionByIndex(0);
    loop.exec();
    EXPECT_EQ(true,ok);
}

TEST(DToolBarTest,toggle_search_buttonstate_true)
{
    DToolBar w;
    w.toggleSearchButtonState(true);
    EXPECT_EQ(true,w.m_searchButtonAsbState);
}

TEST(DToolBarTest,search_bartext_entered_empty)
{
    DToolBar w;
    QString path = QDir::currentPath();
    w.searchBarTextEntered("");
    EXPECT_EQ(path, QDir::currentPath());
    w.handleHotkeyCtrlL(1);
}
